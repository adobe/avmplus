#!/usr/bin/env python
# -*- Mode: Python; indent-tabs-mode: nil -*-
# vi: set ts=4 sw=4 expandtab:

import re

_re_finalSpaces = re.compile(r"(.*) +$")
_re_initialSpaces = re.compile(r" +(.*)$")
_re_finalStar = re.compile(r"(.*)\*$")
_re_finalConst = re.compile(r"(.*) *\bconst$")
_re_initialConst = re.compile(r"const\b *(.*)$")
_re_template = re.compile(r"(.*)<(.*)>$")

_printMangleSubstitutions = False

class MangleScheme:
  def __init__(self, name, cpplatch, func):
    self.name = name;
    self.cpplatch = cpplatch
    self.function = func

  def schemeName(self): return self.name

  def cppLatchBegin(self):
    return "#ifdef %s" % self.cpplatch

  def getCppLatch(self):
    return "%s" % self.cpplatch

  def cppLatchEnd(self):
    return "#endif // def %s" % self.cpplatch

  def mangle(self, name, ret_type, param_types, attributes, typedefs):
    return self.function(name, ret_type, param_types, attributes, typedefs)

# Function attributes are part of the mangled signature on windows
class Attribute:
  NONE                 = 0x0000

  # access controls
  PUBLIC               = 0x0001
  PROTECTED            = 0x0002
  PRIVATE              = 0x0004
  _ACCESS_CONTROL_MASK = 0x000f

  # function types
  STATIC               = 0x0010
  VIRTUAL              = 0x0020
  THUNK                = 0x0040
  _FUNCTION_TYPE_MASK  = 0x00f0

  # export status
  EXPORTED             = 0x0100
  _EXPORT_MASK         = 0x0100

  # calling convensions
  CDECL                = 0x0200
  PASCAL               = 0x0400
  STDCALL              = 0x0800
  THISCALL             = 0x1000
  FASTCALL             = 0x2000
  CLRCALL              = 0x4000
  _CALLING_CONV_MASK   = 0x7e00


#
# GCC-style name mangler.
#
# The best reference is the Itanium C++ ABI
#   http://google.com/search?q=Itanium+C%2B%2B+ABI
#
# These links might still work too:
#   http://www.agner.org/optimize/calling_conventions.pdf
#   http://mentorembedded.github.com/cxx-abi/abi.html#mangling
# 
def _gcc_mangle(name, ret_type, param_types, attributes, typedefs):
  subs = []
  mangle_map = {
    'void': 'v',
    'wchar_t': 'w',
    'char': 'c',
    'signed char': 'a',
    'unsigned char': 'h',
    'short': 's',
    'unsigned short': 't',
    'int': 'i',
    'unsigned int': 'j',
    'unsigned': 'j',
    'long': 'l',
    'unsigned long': 'm',
    'long long': 'x',
    'unsigned long long': 'y',
    'double': 'd',
    'float': 'f',
  }

  # Encode each name part as <len><str>
  def make_name(ident):
    return str(len(ident)) + ident

  def base36(n):
   if (n < 36):
     return '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'[n]
   return base36(n/36)+base36(n%36)

  # Find a substitution, and do not record future substitution
  def find_subst(nm):
    if nm in subs:
      i = subs.index(nm)
      if i == 0:
        return 'S_'
      else:
        return 'S'+base36(i-1)+'_'
    return nm

  # Perform a substitution if possible; if not record a possible future substitution
  def do_subst(nm, subst=None):
    if subst == None:
      subst = nm
    if nm in subs:
      i = subs.index(nm)
      if i == 0:
        return 'S_'
      else:
        return 'S'+base36(i-1)+'_'
    subs.append(subst)
    if _printMangleSubstitutions:
      print subs
    return nm

  # Each namespace prefix is encoded and substitutions are performed
  def encode_namespaces(parts):
    if len(parts) > 1:
      return do_subst(encode_namespaces(parts[:-1])+make_name(parts[-1]))
    return do_subst(make_name(parts[0]))

  # Record the namespace prefixes and the typename in the substitution table
  # A composite of encoded namespaces and a name is encoded N <encoded_namespace>+ <encoded_name> E
  def encode_type_name(nm):
    nm_parts = nm.split('::')
    if len(nm_parts) > 1:
      return do_subst('N'+encode_namespaces(nm_parts[:-1])+make_name(nm_parts[-1])+'E')
    return do_subst(make_name(nm))

  # record the namespace prefixes in the substitutions table but not the function name
  def encode_function_name(nm):
    nm_parts = nm.split('::')
    if len(nm_parts) > 1:
      return 'N'+encode_namespaces(nm_parts[:-1])+make_name(nm_parts[-1])+'E'
    return make_name(nm)

  def encode_type(nm):
    m = _re_initialSpaces.match(nm) or _re_finalSpaces.match(nm)
    if m:
      return encode_type(m.group(1))

    m = _re_finalStar.match(nm)
    if m:
      t = encode_type(m.group(1))
      return do_subst('P'+t, 'P'+find_subst(t))

    m = _re_initialConst.match(nm) or _re_finalConst.match(nm)
    if m:
      t = encode_type(m.group(1))
      return do_subst('K'+t,'K'+find_subst(t))

    while nm in typedefs:
      nm = typedefs[nm]

    if nm in mangle_map:
      return mangle_map[nm]

    return encode_type_name(nm)

  res = '_Z'+encode_function_name(name)
  for param_type in param_types:
    res += encode_type(param_type)
  if len(param_types) == 0:
      res += 'v'
  return res

# Partial MSVC C++ mangler.  There are a number of assumptions based on the
# current functions we're mangling.  It may be possible we'll run into a
# function which violates some of our assumptions, and some part of this may 
# have to be updated.
# Reference: http://mearie.org/documents/mscmangle/
def _msvc_mangle(name, ret_type, param_types, attributes, typedefs):
  mangle_map = {
    # '(reference)' :'A' 
    # '(volatile)' :'B' 
    'signed char' : 'C',
    'char' : 'D',
    '__int8' : '_D',
    'unsigned char' : 'E',
    'unsigned __int8' : '_E',
    'short' : 'F',
    '__int16' : '_F',
    'unsigned short' : 'G',
    'unsigned __int16' : '_G',
    'int' : 'H',
    '__int32' : '_H',
    'unsigned int' : 'I',
    'unsigned' : 'I',
    'unsigned __int32' : '_I',
    'long' : 'J',
    '__int64' : '_J',
    'unsigned long' : 'K',
    'unsigned __int64' : '_K',
    '__int128' : '_L',
    'float' : 'M',
    'unsigned __int128' : '_M',
    'double' : 'N',
    'bool' : '_N',
    'long double' : 'O',
    # '(array)' : '_O',
    # '(pointer)' : 'P',
    # '(const pointer)' : 'Q',
    # '(volatile pointer)' : 'R',
    # '(const volatile pointer)' : 'S',
    # '(union)' : 'T',
    # '(struct)' : 'U',
    # '(class)' : 'V',
    # '(enum)' : 'W',
    'wchar_t' : '_W',
    'void' : 'X',
    '(cointerface)' : 'Y',
    '(...)' : 'Z',
  }

  _af_ft_encoding = {
    Attribute.PRIVATE   | Attribute.NONE:    'A',
    Attribute.PRIVATE   | Attribute.STATIC:  'C',
    Attribute.PRIVATE   | Attribute.VIRTUAL: 'E',
    Attribute.PRIVATE   | Attribute.THUNK:   'G',
    Attribute.PROTECTED | Attribute.NONE:    'I',
    Attribute.PROTECTED | Attribute.STATIC:  'K',
    Attribute.PROTECTED | Attribute.VIRTUAL: 'M',
    Attribute.PROTECTED | Attribute.THUNK:   'O',
    Attribute.PUBLIC    | Attribute.NONE:    'Q',
    Attribute.PUBLIC    | Attribute.STATIC:  'S',
    Attribute.PUBLIC    | Attribute.VIRTUAL: 'U',
    Attribute.PUBLIC    | Attribute.THUNK:   'W',
    Attribute.NONE      | Attribute.NONE:    'Y'
  }

  _cc_encoding = {
    Attribute.NONE     | Attribute.CDECL:    'A',
    Attribute.EXPORTED | Attribute.CDECL:    'B',
    Attribute.NONE     | Attribute.PASCAL:   'C',
    Attribute.EXPORTED | Attribute.PASCAL:   'D',
    Attribute.NONE     | Attribute.THISCALL: 'E',
    Attribute.EXPORTED | Attribute.THISCALL: 'F',
    Attribute.NONE     | Attribute.STDCALL:  'G',
    Attribute.EXPORTED | Attribute.STDCALL:  'H',
    Attribute.NONE     | Attribute.FASTCALL: 'I',
    Attribute.EXPORTED | Attribute.FASTCALL: 'J',
    Attribute.NONE     | Attribute.NONE:     'K',
    Attribute.EXPORTED | Attribute.NONE:     'L',
    Attribute.NONE     | Attribute.CLRCALL:  'M'
  }


  def encode_function_type(attrs):
    v = attrs & (Attribute._ACCESS_CONTROL_MASK | Attribute._FUNCTION_TYPE_MASK)
    if not v in _af_ft_encoding:
      raise Exception("Invalid combination of access flags and/or function type")
    else:
      return _af_ft_encoding[v]

  def encode_cv_modifier(attrs):
    # ASSUMPTION: we aren't used __based() methods
    if (attrs & Attribute.STATIC) == Attribute.STATIC:
      return '' 
    else: return 'A'

  def encode_calling_conv(attrs):
    v = attrs & (Attribute._EXPORT_MASK | Attribute._CALLING_CONV_MASK)
    if not v in _cc_encoding:
      raise Exception("Invalid combination of export and/or calling conv")
    else:
      return _cc_encoding[v]

  def encode_name(n, cache):
    if n == '': return ''

    m = _re_template.match(n)
    if m:
      return encode_template(m.group(1), m.group(2), encode_name)

    if n in cache:
      return cache.get(n)
    else:
      cache[n] = str(len(cache))
      return n + '@'

  def encode_qname(qn, cache):
    res = ''
    rn = qn.split("::")
    rn.reverse();
    for n in rn:
      res += encode_name(n, cache)
    res += '@'  
    return res

  def encode_return_type(nm, name_cache):
    while nm in typedefs:
      nm = typedefs[nm]

    # ASSUMPTION: return value enums appear to get 
    # an anonymous namespace specification.  
    ns = ''
    if nm in mangle_enums:
      ns ='?A'
    return ns + encode_type(nm, name_cache, '')

  def encode_param_type(nm, name_cache, param_cache):
    # primitives (or typedefed primitives) don't do 
    # back references
    while nm in typedefs:
      nm = typedefs[nm]
    if nm in mangle_map:
      return mangle_map[nm]

    if nm in param_cache:
      return param_cache.get(nm)
    else:
      param_cache[nm] = str(len(param_cache))
      return encode_type(nm, name_cache, '')

  def encode_template(name, temp_params, encoding_func):
    # This encoding is completely untested, and for the moment, unused.
    # It should be pretty close to what we need to do though.
    parameter_cache = {}
    name_cache = {}
    params = temp_params.split(",")
    res = '?$' + encoding_func(name, name_cache, '')
    for p in params:
      res += encode_param_type(p, name_cache, parameter_cache)
    res += '@'
    return res;

  def encode_type(nm, name_cache, constQual):
    while nm in typedefs:
      nm = typedefs[nm]

    m = _re_template.match(nm)
    if m:
      return encode_template(m.group(1), m.group(2), encode_type)

    m = _re_initialSpaces.match(nm) or _re_finalSpaces.match(nm)
    if m:
      return encode_type(m.group(1), name_cache, constQual)

    m = _re_finalStar.match(nm)
    if m:
      if constQual == '': constQual = 'A'
      return 'P' + encode_type(m.group(1), name_cache, constQual)

    m = _re_initialConst.match(nm) or _re_finalConst.match(nm)
    if m:
      return encode_type(m.group(1), name_cache, 'B')

    if nm in mangle_enums:
      sz = str(mangle_enums[nm])
      return constQual + 'W' + sz + encode_qname(nm, name_cache)

    if nm in mangle_map:
      return constQual + mangle_map[nm]

    # ASSUMPTION: class if non-primitive and non-enum
    return constQual + 'V' + encode_qname(nm, name_cache)

  name_cache = {}
  param_cache = {}
  res = '?' + encode_qname(name, name_cache)
  res += encode_function_type(attributes)
  res += encode_cv_modifier(attributes)
  res += encode_calling_conv(attributes)
  res += encode_return_type(ret_type, name_cache)

  if len(param_types) > 0:
    for t in param_types:
      res += encode_param_type(t, name_cache, param_cache)
    res += '@'
  else:
    res += 'X'

  res += 'Z' # ASSUMPTION: no throws
  return res

mangleSchemes = [ 
  MangleScheme('gcc', '__GNUC__', _gcc_mangle),
  MangleScheme('msvc', '_MSC_VER', _msvc_mangle)
]


# Generate a string that can easily be parsed into an LLVM::Type
def make_llvm_type_string(name, typedefs):
  type_map = {
    'void': 'v',
    'char': 'c',
    'signed char': 'c',
    'unsigned char': 'c',
    'short': 's',
    'unsigned short': 's',
    'int': 'i',
    'unsigned int': 'i',
    'unsigned': 'i',
    'long': 'i',
    'unsigned long': 'i',
    'long long': 'x',
    'unsigned long long': 'x',
    'double': 'd',
    'float': 'f',
  }

  def encode_type(nm):
    m = (_re_initialSpaces.match(nm) or _re_finalSpaces.match(nm) or
        _re_initialConst.match(nm) or _re_finalConst.match(nm))
    if m:
      return encode_type(m.group(1))

    m = _re_finalStar.match(nm)
    if m:
      return '*'+  encode_type(m.group(1))

    while nm in typedefs:
      nm = typedefs[nm]

    if nm in type_map:
      return type_map[nm]

    return "'" + nm + "'"

  return encode_type(name)

mangle_typedefs_32 = {
    'int32_t': 'int',
    'uint32_t': 'unsigned',
    'int64_t': 'long long',
    'uint64_t': 'unsigned long long',
    'Atom': 'int32_t',
    'avmplus::Atom': 'int32_t',
    'ClassClosure': 'avmplus',
    'MethodFrame': 'avmplus::MethodFrame',
    'MethodEnv': 'avmplus::MethodEnv',
    'MethodInfo': 'avmplus::MethodInfo',
    'Multiname': 'avmplus::Multiname',
    'Namespace': 'avmplus::Namespace',
    'String': 'avmplus::String',
    'Traits': 'avmplus::Traits',
    'ScriptObject': 'avmplus::ScriptObject',
    'ArrayObject': 'avmplus::ArrayObject',
    'IntVectorObject': 'avmplus::IntVectorObject',
    'UIntVectorObject': 'avmplus::UIntVectorObject',
    'DoubleVectorObject': 'avmplus::DoubleVectorObject',
    'ClassClosure': 'avmplus::ClassClosure',
}

mangle_typedefs_64 = {
    'int32_t': 'int',
    'uint32_t': 'unsigned',
    'int64_t': 'long long',
    'uint64_t': 'unsigned long long',
    'Atom': 'int64_t',
    'avmplus::Atom': 'int64_t',
    'ClassClosure': 'avmplus',
    'MethodFrame': 'avmplus::MethodFrame',
    'MethodEnv': 'avmplus::MethodEnv',
    'MethodInfo': 'avmplus::MethodInfo',
    'Multiname': 'avmplus::Multiname',
    'Namespace': 'avmplus::Namespace',
    'String': 'avmplus::String',
    'Traits': 'avmplus::Traits',
    'ScriptObject': 'avmplus::ScriptObject',
    'ArrayObject': 'avmplus::ArrayObject',
    'IntVectorObject': 'avmplus::IntVectorObject',
    'UIntVectorObject': 'avmplus::UIntVectorObject',
    'DoubleVectorObject': 'avmplus::DoubleVectorObject',
    'ClassClosure': 'avmplus::ClassClosure',
}

# enums: { name: sizeof(basetype) } 
mangle_enums = {
    'BoolKind': 4,
}

def getAvmMangleTypedefs(arch):
    return mangle_typedefs_32 if (arch == 32) else mangle_typedefs_64

# Some test cases
if __name__ == "__main__":
    _printMangleSubstitutions = True
    for ms in mangleSchemes:
      print ms.mangle("foo", "void", ["MethodFrame*", "Traits*"] , mangle_typedefs_32)
      print ms.mangle("halfmoon::Stubs::do_abc_getprop", "int", ["MethodFrame*", "const Multiname*", "int"] , mangle_typedefs_32)
      print ms.mangle("halfmoon::Stubs::do_abc_getprop", "void", ["MethodFrame*", "Multiname const*", "int"] , mangle_typedefs_32)
      print ms.mangle("halfmoon::Stubs::do_abc_getprop", "void", ["MethodFrame*", "Multiname* const", "int"] , mangle_typedefs_32)
      # halfmoon::Stubs::do_concat_strings(avmplus::MethodFrame*, avmplus::String*, avmplus::String*)
      # S_        S0_                      S1_      S2_       S3_          S4_  S5_
      print ms.mangle("halfmoon::Stubs::do_concat_strings", "void", ["MethodFrame*", "String*", "String*"] , mangle_typedefs_32)

