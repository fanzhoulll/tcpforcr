/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Adrian Sai-wah Tam
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Adrian Sai-wah Tam <adrian.sw.tam@gmail.com>
 */

#ifndef TCP_CR_H
#define TCP_CR_H

#include "tcp-socket-base.h"

namespace ns3 {

/**
 * \ingroup socket
 * \ingroup tcp
 *
 * \brief An implementation of a stream socket using TCP.
 *
 * This class contains the NewReno implementation of TCP, as of \RFC{2582}.
 */
class TcpCR : public TcpSocketBase
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  /**
   * Create an unbound tcp socket.
   */
  TcpCR (void);
  /**
   * \brief Copy constructor
   * \param sock the object to copy
   */
  TcpCR (const TcpCR& sock);
  virtual ~TcpCR (void);

protected:
  virtual Ptr<TcpSocketBase> Fork (void); // Call CopyObject<TcpCR> to clone me
  virtual void NewAck (SequenceNumber32 const& seq); // Inc cwnd and call NewAck() of parent
  virtual void DupAck (const TcpHeader& t, uint32_t count);  // Halving cwnd and reset nextTxSequence
  virtual void Retransmit (void); // Exit fast recovery upon retransmit timeout
  virtual void ReceivedAck (Ptr<Packet> packet, const TcpHeader& tcpHeader); // Process received ACK

protected:
  SequenceNumber32       m_recover;      //!< Previous highest Tx seqnum for fast recovery
  uint32_t               m_retxThresh;   //!< Fast Retransmit threshold
  bool                   m_inFastRec;    //!< currently in fast recovery
  bool                   m_limitedTx;    //!< perform limited transmit

  // For estimate bandwidth quickly
  double                 m_ackSeqStartNum;
  double                 m_ackSeqEndNum;
  double                 m_ackSeqStartTime;
  double                 m_ackSeqEndTime;
  double                 m_ackSeqCount;
  double                 m_ackSeqLength;
  Time                   m_minRtt;

  uint32_t               test;
};

} // namespace ns3

#endif /* TCP_NEWRENO_H */
