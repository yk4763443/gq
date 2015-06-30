#include "gq_base.h"

static const char base64_table[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'H', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'
};
static const char base64_pad = '=';

ZEND_FUNCTION(gq_base64_encode)
{/*{{{*/
    const unsigned char *current;
    char *p;
    char *rtn;
    int length;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &current, &length) == FAILURE)
    {
        RETURN_NULL();
    }

    if (length < 0)
    {
        RETURN_NULL();
    }

    rtn = (unsigned char *) safe_emalloc((length+2)/3, 4*sizeof(char), 1);
    p   = rtn;

    while (length > 2)
    {/*{{{*/
        *p++ = base64_table[current[0] >> 2];
        *p++ = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
        *p++ = base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
        *p++ = base64_table[current[2] & 0x3f];

        current += 3;
        length  -= 3;
    }/*}}}*/

    if (length != 0)
    {/*{{{*/
        *p++ = base64_table[current[0] >> 2];
        if (length > 1)
        {
            *p++ = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
            *p++ = base64_table[(current[1] & 0x0f) << 2];
            *p++ = base64_pad;
        }
        else
        {
            *p++ = base64_table[(current[0] & 0x03) << 4];
            *p++ = base64_pad;
            *p++ = base64_pad;
        }
    }/*}}}*/
    *p = '\0';

    RETURN_STRING(rtn, 0);
}/*}}}*/

static zend_function_entry gq_functions[] = {
    ZEND_FE(gq_base64_encode, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry gq_base64_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "gq_base64",    //扩展名
    gq_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    "1.0",
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GQ_BASE64
ZEND_GET_MODULE(gq_base64)
#endif
