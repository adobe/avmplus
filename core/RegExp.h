/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __avmplus_RegExp__
#define __avmplus_RegExp__

#include "avmplus.h"

#define PCRE2_CODE_UNIT_WIDTH 8
#define PCRE2_STATIC

#ifdef VMCFG_PCRE2
#include "../pcre2/include/pcre2.h"
#endif
#include "pcre.h"


namespace avmplus
{

struct RegExpCompileData
    {
    public:
        pcre *m_pcre1;
#ifdef VMCFG_PCRE2
        pcre2_code *m_pcre2;
#endif
        void *getCompiled();
        bool isNull();
    };

struct RegExpSptrType
    {
    public:
        RegExpSptrType(const char *string);
        PCRE_SPTR m_pcre1;
#ifdef VMCFG_PCRE2
        PCRE2_SPTR m_pcre2;
#endif
    };
    
class RegExpSizeType;
    
class RegExp
    {
    private:
        static bool m_pcre2;
        bool isCopy;
        RegExpCompileData m_compiledData;
#ifdef VMCFG_PCRE2
        pcre2_match_data *m_matchData;
        pcre2_general_context *m_gcontext;
        pcre2_compile_context *m_ccontext;
        pcre2_match_context *m_mcontext;
#endif
    
    public:
        RegExp(): isCopy(0)
#ifdef VMCFG_PCRE2
            , m_matchData(0)
#endif
            {
            m_compiledData.m_pcre1 = NULL;
#ifdef VMCFG_PCRE2
            m_compiledData.m_pcre2 = NULL;

            
            if(m_pcre2)
            {
                m_gcontext = pcre2_general_context_create(private_malloc, private_free, NULL);
                m_ccontext = pcre2_compile_context_create(m_gcontext);
                m_mcontext = pcre2_match_context_create(m_gcontext);
            }
#endif
        }
        RegExp(RegExp *regex): isCopy(true)
        {
#ifdef VMCFG_PCRE2
            m_gcontext = regex->m_gcontext;
            m_ccontext = regex->m_ccontext;
            m_mcontext = regex->m_mcontext;
            m_matchData = NULL;
            m_compiledData.m_pcre2 = regex->m_compiledData.m_pcre2;
#endif
            m_compiledData.m_pcre1 = regex->m_compiledData.m_pcre1;
        }
        
        ~RegExp();
        static bool isPcre2() { return m_pcre2; }
        static void InitializeRegExp(bool isPcre2);
        
        bool compile(RegExpSptrType pattern, int patternLength, int options, const char **errorptr, int *erroroffset, const unsigned char *tables);
        int exec(RegExpSptrType subject, int length, int start_offset, int options, RegExpSizeType &matchVector);
        int fullinfo(int what, void *where);
        int getString(const char *subject, RegExpSizeType &matchVector, int stringcount, int stringnumber, const char **stringptr);
        RegExpCompileData getCompiledData();

        static int kUtfOption;
        static int kNoUtfOption;
        static int kCaselessOption;
        static int kMultilineOption;
        static int kDotallOption;
        static int kExtendedOption;
        static int kInfoNameEntrySize;
        static int kInfoNameCount;
        static int kInfoNameTable;
        
        //memory handler
        static void *private_malloc(size_t size, void *data)
        {
            (void)data;
            //return mmfx_new_array(char, size);
            return mmfx_new_array_opt(char, size, MMgc::kZero);
        }
        
        static void private_free(void *block, void *data)
        {
            (void)data;
            char *cp = (char *) block;
            mmfx_delete_array(cp);
        }
        
        bool copy()
        {
            return isCopy;
        }

    };

class RegExpSizeType
    {
    public:
        int m_size;
        union
        {
            int *m_pcre1;
#ifdef VMCFG_PCRE2
            PCRE2_SIZE *m_pcre2;
#endif
        };
        
    public:
        RegExpSizeType(int size): m_size(size)
        {
            if(!RegExp::isPcre2())
                m_pcre1 = mmfx_new_array(int, m_size);
        }
        
        ~RegExpSizeType()
        {
            if(!RegExp::isPcre2())
                mmfx_delete_array(m_pcre1);
        }
        
        RegExpSizeType(): m_size(0) { }
        
        int getSize()
        {
            return m_size;
        }
        
        int getIndex(int i)
        {
#ifdef VMCFG_PCRE2
            if(RegExp::isPcre2())
                return (int)m_pcre2[i];
#endif
            return m_pcre1[i];
        }
    };
}

#endif /* __avmplus_RegExp__ */
