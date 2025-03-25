#include "tsTransportStream.h"

//=============================================================================================================================================================================
// xTS_PacketHeader
//=============================================================================================================================================================================


/// @brief Reset - reset all TS packet header fields
void xTS_PacketHeader::Reset()
{
  m_SB = m_E = m_S = m_PID = m_TSC = m_AFC = m_CC = 0;
}

/**
  @brief Parse all TS packet header fields
  @param Input is pointer to buffer containing TS packet
  @return Number of parsed bytes (4 on success, -1 on failure) 
 */
int32_t xTS_PacketHeader::Parse(const uint8_t* Input)
{
  const uint32_t* HeadPtr = (const uint32_t*)Input;
  uint32_t Head = xSwapBytes32(*HeadPtr);

  m_SB = (uint8_t)((Head & 0xFF000000) >> 24);
  m_E = (uint8_t)((Head & 0x00800000) >> 23);
  m_S = (uint8_t)((Head & 0x00400000) >> 22);
  m_T = (uint8_t)((Head & 0x00200000) >> 21);
  m_PID = (uint16_t)((Head & 0x001FFF00) >> 8);
  m_TSC = (uint8_t)((Head & 0x000000C0) >> 6);
  m_AFC = (uint8_t)((Head & 0x00000030) >> 4);
  m_CC = (uint8_t)((Head & 0x0000000F) >> 0);

  return 4;
}

/// @brief Print all TS packet header fields
void xTS_PacketHeader::Print() const
{
  printf(" TS: ");
  printf(" SB=%u ", m_SB);
  printf(" E=%u ", m_E);
  printf(" S=%u ", m_S);
  printf(" P=%u ", m_T);
  printf(" PID=%u ", m_PID);
  printf(" TSC=%u ", m_TSC);
  printf(" AF=%u ", m_AFC);
  printf(" CC=%u ", m_CC);
}

//=============================================================================================================================================================================
