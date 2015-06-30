#ifndef GQ_BASE_H
#define GQ_BASE_H

#include <stdio.h>
#include <stdlib.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#define phpext_gq_base64_ptr &gq_base64_module_entry
extern zend_module_entry gq_base64_module_entry;
#endif
