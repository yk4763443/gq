PHP_ARG_ENABLE(gq_base64, [Whether to enable the "gq_base64" extension], [ enable-gq_base64    Enable "gq_base64" extension support])

if test $PHP_GQ_BASE64 != "no"; then
  PHP_SUBST(GQ_BASE64_SHARED_LIBADD)
  PHP_NEW_EXTENSION(gq_base64, gq_base.c, $ext_shared)
fi
