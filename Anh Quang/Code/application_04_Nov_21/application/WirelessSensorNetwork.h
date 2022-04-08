#ifndef _WIRELESSSENSORNETWORK_DEFINE_H
#define _WIRELESSSENSORNETWORK_DEFINE_H

/***********************************************
* Type definition
***********************************************/
/*
* @brief Initialize Array values with 0xFF
* @param[in] assg[] Value of Array to initialize
* @param[in] next[] the Array containing next index  needs to initialize
* @param[in] None
* @return none
*/

//void InitializeArray(uint8_t assg[], uint8_t next[], uint8_t const MAX);
/*
*@brief Check value already in Array
* @param[in] assg[] the value of element in Array
* @param[in] next[] the Array containing next index
* @param[in] head   the head index of linked list
* @param[in] value   the value to check
* @return True if the value adready exist in Array, false if not exist
*/
//bool CheckValueExist(uint8_t assg[], uint8_t next[], uint8_t const head, uint8_t const value );
/*
*@brief Add Element in Array
* @param[in] assg[] the value of element in Array
* @param[in] next[] the Array containing next index
* @param[in] head   the head index of linked list
* @param[in] value   the value to check
* @return True if the value adready exist in Array, false if not exist
*/
//uint8_t AddElement(uint8_t assg[], uint8_t next[], uint8_t* addrHead, uint8_t const addIndex);
/*
*@brief DeleteElement an element out of the Array
* @param[in] assg[] the value of   Array
* @param[in] next[] the Array containing next index
* @param[in] AddrHead the adress of head index of linked list
* @param[in] AddIndex  the index của element
* @retval    The index of element before element just deleled, if you DeleteElement element in the front, \
it will return the index of element after it
*/
//uint8_t DeleteElement(uint8_t assg[], uint8_t next[], uint8_t* addrHead, uint8_t const value);
#endif /* _WIRELESSSENSORNETWORK_DEFINE_H */
/* [] END OF FILE */
