/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "RegExp.h"

namespace avmplus
{
    using namespace MMgc;
    
    //Default is PCRE 1
    bool RegExp::m_pcre2 = 0;
    
    //defining options for pcre
    int RegExp::kUtfOption = PCRE_UTF8;
    int RegExp::kNoUtfOption = PCRE_NO_UTF8_CHECK;
    int RegExp::kCaselessOption = PCRE_CASELESS;
    int RegExp::kMultilineOption = PCRE_MULTILINE;
    int RegExp::kDotallOption = PCRE_DOTALL;
    int RegExp::kExtendedOption = PCRE_EXTENDED;
    int RegExp::kInfoNameEntrySize = PCRE_INFO_NAMEENTRYSIZE;
    int RegExp::kInfoNameCount = PCRE_INFO_NAMECOUNT;
    int RegExp::kInfoNameTable = PCRE_INFO_NAMETABLE;

    void RegExp::InitializeRegExp(bool isPcre2)
    {
		(void)isPcre2;
        RegExp::m_pcre2 = isPcre2;

#ifdef VMCFG_PCRE2
        if(m_pcre2)
        {
            kUtfOption = PCRE2_UTF;
            kNoUtfOption = PCRE2_NO_UTF_CHECK;
            kCaselessOption = PCRE2_CASELESS;
            kMultilineOption = PCRE2_MULTILINE | PCRE2_NEWLINE_CR;
            kDotallOption = PCRE2_DOTALL;
            kExtendedOption = PCRE2_EXTENDED;
            kInfoNameEntrySize = PCRE2_INFO_NAMEENTRYSIZE;
            kInfoNameCount = PCRE2_INFO_NAMECOUNT;
            kInfoNameTable = PCRE2_INFO_NAMETABLE;
        }
#endif
    }
    
    RegExp::~RegExp()
    {
            if(!m_pcre2)
            {
                if(!isCopy)
                    pcre_free(m_compiledData.m_pcre1);
            }
#ifdef VMCFG_PCRE2
            else
            {
                if(!isCopy)
                {
                    pcre2_code_free(m_compiledData.m_pcre2);
                    pcre2_compile_context_free(m_ccontext);
                    pcre2_match_context_free(m_mcontext);
                    pcre2_general_context_free(m_gcontext);
                }
                pcre2_match_data_free(m_matchData);

            }
#endif
    }
    
    //Returns compiled string for the pattern given
    bool RegExp::compile(RegExpSptrType pattern, int patternLength, int options, const char **errorptr, int *erroroffset, const unsigned char *tables)
    {
#ifdef VMCFG_PCRE2
        if(m_pcre2)
        {
            int pcre2errorptr;
            size_t pcre2erroroffset;
            m_compiledData.m_pcre2 = pcre2_compile(pattern.m_pcre2, patternLength, (uint32_t)(options | PCRE2_ALLOW_EMPTY_CLASS | PCRE2_ALT_BSUX | PCRE2_MATCH_UNSET_BACKREF), &pcre2errorptr, &pcre2erroroffset, m_ccontext);

            if (m_compiledData.m_pcre2 == NULL)
            {
                PCRE2_UCHAR buffer[256];
                pcre2_get_error_message(pcre2errorptr, buffer, sizeof(buffer));
                //assert(false);
            }
            return m_compiledData.isNull() ? false : true;
        }
#endif
        {
			(void)patternLength;
            m_compiledData.m_pcre1 = pcre_compile(pattern.m_pcre1, options, errorptr, erroroffset, tables);
        }

        return m_compiledData.isNull() ? false : true;
    }
    
    int RegExp::exec(RegExpSptrType subject, int length, int start_offset, int options, RegExpSizeType &matchVector)
    {
#ifdef VMCFG_PCRE2
        if(m_pcre2)
        {
            if( m_matchData )
                pcre2_match_data_free(m_matchData);
            
            m_matchData = m_compiledData.m_pcre2 ? pcre2_match_data_create_from_pattern(m_compiledData.m_pcre2, m_gcontext) : NULL;
            int val = pcre2_match(m_compiledData.m_pcre2, subject.m_pcre2, length, start_offset, options, m_matchData, m_mcontext);
            /* Matching failed: handle error cases */
            
            if (val < 0)
            {
                //assert(false);
            }
            else
            {
                matchVector.m_pcre2 = pcre2_get_ovector_pointer(m_matchData);
                matchVector.m_size = pcre2_get_ovector_count(m_matchData);
                val = matchVector.getSize();
            }

            return val;
        }
#endif
        {
            const pcre_extra *extra_data = NULL;
            return pcre_exec(m_compiledData.m_pcre1, extra_data, subject.m_pcre1, length, start_offset, options, matchVector.m_pcre1, matchVector.getSize());
        }
    }
    
    int RegExp::getString(const char *subject, RegExpSizeType &matchVector, int stringcount, int stringnumber, const char **stringptr)
    {
#ifdef VMCFG_PCRE2
        if(m_pcre2)
        {
            PCRE2_SIZE len;
            return pcre2_substring_get_bynumber( m_matchData, stringnumber, (unsigned char**)stringptr, &len);
            (void)len;
        }
#endif
        {
            return pcre_get_substring( subject, matchVector.m_pcre1, stringcount, stringnumber, stringptr );
        }
    }
    
    int RegExp::fullinfo(int what, void *where)
    {
#ifdef VMCFG_PCRE2
        if(m_pcre2)
        {
            return pcre2_pattern_info(m_compiledData.m_pcre2, what, where);
        }
#endif
		{
            const pcre_extra *extra_data = NULL;
            return pcre_fullinfo(m_compiledData.m_pcre1, extra_data, what, where);
        }
        
    }

    RegExpCompileData RegExp::getCompiledData()
    {
        return m_compiledData;
    }
    
    RegExpSptrType::RegExpSptrType(const char *string)
    {
        if(!RegExp::isPcre2())
            m_pcre1 = string;
#ifdef VMCFG_PCRE2
        else
            m_pcre2 = (const unsigned char*)string;
#endif
    }
    
    void *RegExpCompileData::getCompiled()
    {
#ifdef VMCFG_PCRE2
        if(RegExp::isPcre2())
            return (void*)m_pcre2;
#endif
		return (void*)m_pcre1;
    }
    
    bool RegExpCompileData::isNull()
    {
#ifdef VMCFG_PCRE2
        if(RegExp::isPcre2())
            return m_pcre2 == NULL ? true : false;
#endif
        return m_pcre1 == NULL ? true : false;
    }

}
