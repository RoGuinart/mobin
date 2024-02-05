
#ifndef _MOBIN_H_
#define _MOBIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \brief Converts a string to mobin
 * 
 * \param str   String to convert
 * \param mobin Outputted mobin
 * \param mlen  Maximum length of the mobin string.
 *              Remember that mobin can go from x0.5 to x4.25 the length
 *              of the original string. In case of overflow, an error shall
 *              be returned.
 * 
 * \return 0 on success, -1 on error
 */
int strtomobin(char *str, char *mobin, long mlen);

/**
 * \brief Converts a mobin string back to alphanumeric
 * 
 * \param mobin Mobin string to convert
 * \param str   Resulting string
 * \param slen Maximum length of the result string.
 * 
 * \return 0 on success, -1 on error
 */
int mobintostr(char *mobin, char *str, long slen);


#ifdef __cplusplus
}
#endif
#endif // _MOBIN_H_