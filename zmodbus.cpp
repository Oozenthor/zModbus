#include "zmodbus.h"
QList<quint16> replyList;
quint16 replyTid;

//##############################################################
ZModbus::ZModbus(QWidget *parent)
{
  tcpSocket = new QTcpSocket(this);
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(mbRead()));
  tcpSocket->connectToHost("127.0.0.1",502);

  qDebug() << "valid: " << tcpSocket->isValid();
}

ZModbus::~ZModbus()
{
}

//##############################################################
// Public functions
/*
//--------------------------------------------------------------
// 0xxxx Discrete Outputs
// 0x01 ReadCoils
QBitArray ZModbus::ReadCoils(quint16 addr, quint16 qty)
{

}

// 0x05 WriteSingleCoil
bool ZModbus::WriteSingleCoil(quint16 addr, bool val)
{

}

// 0x0F WriteMultipleCoils
bool ZModbus::WriteMultipleCoils(quint16 addr, QList<bool> val)
{

}

//--------------------------------------------------------------
// 1xxxx Discrete Inputs
// 0x02 ReadDiscreteInputs
QBitArray ZModbus::ReadDiscreteInputs(quint16 addr, quint16 qty)
{

}

//--------------------------------------------------------------
// 3xxxx Input Registers
// 0x04 ReadInputRegisters
QList<quint16> ZModbus::ReadInputRegisters(quint16 addr, quint16 qty)
{

}
*/
//--------------------------------------------------------------
// 4xxxx Holding Registers
// 0x03 ReadHoldingRegisters
QList<quint16> ZModbus::ReadHoldingRegisters(quint16 addr, quint16 qty)
{
  quint16 tid = 1;
  qDebug() << "tx fc03";

  replyTid = 0;
  tx03(tid, addr, qty);
  while( tid != replyTid ) { }

  return(replyList);
}

// 0x06 WriteSingleRegister
bool ZModbus::WriteSingleRegister(quint16 addr, quint16 val)
{
  qDebug() << "tx fc06";
  quint16 tid = 1;
  tx06(tid, addr, val);
  return(1);
}

// 0x10 WriteMultipleRegisters
bool ZModbus::WriteMultipleRegisters(quint16 addr, quint16 val)
{
  qDebug() << "tx fc10";
  quint16 tid = 1;
  //    tx10(tid, addr, val);
  return(1);
}

//##############################################################
// Private slots

void ZModbus::mbRead()
{
  ZModbus::mbReplyType mbReply; //

  QByteArray tcpFrame = tcpSocket->readAll(); // Read TCP socket
  mbReply =  ZModbus::tcpToModbusReply(tcpFrame);

  replyTid = mbReply.tid;
  qDebug() << "fc:" << mbReply.fc;
  switch (mbReply.fc) {
  case FC_03:
    replyList = ZModbus::rx03(mbReply.data);
    break;
  case FC_06:
    break;

  case FC_10:
    break;
  default:
    break;
  }
}

//##############################################################
// Private functions
//
// A very common transaction form
// 6 word size requests {16 tid + 16 PID + 16 len + 8 UID + 8 fc + 16 addr + 16 data = 6 x 16 bits }
QByteArray ZModbus::tx6W(quint16 tid, quint8 fc, quint16 addr, quint16 data)
{
  QByteArray tcpFrame;
  QDataStream tcpStream(&tcpFrame, QIODevice::WriteOnly);
  quint16 len = 6; // Modbus frame length

  tcpStream << tid << PID << len << UID << fc << addr << data;
  //  qDebug() << "tx4r->" << tcpFrame.toHex();
  return(tcpFrame); // TCP frame for transmission
}

//**************************************************************
// tx rx implementation for each function code type
//--------------------------------------------------------------
// 0xxxx Discrete Outputs
// 0x01 ReadCoils
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 0x05 WriteSingleCoil
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 0x0F WriteMultipleCoils

//--------------------------------------------------------------
// 1xxxx Discrete Inputs
// 0x02 ReadDiscreteInputs

//--------------------------------------------------------------
// 3xxxx Input Registers
// 0x04 ReadInputRegisters

//--------------------------------------------------------------
// 4xxxx Holding Registers
// 0x03 ReadHoldingRegisters
QByteArray ZModbus::tx03(quint16 tid, quint16 addr, quint16 qty)
{
  QByteArray tcpFrame = tx6W(tid, FC_03, addr, qty);
  return(tcpFrame); // TCP frame for transmission
}

QList<quint16> ZModbus::rx03(QByteArray &mbData)
{
  quint8 byteCount; //Count of how many data bytes in recieved frame
  QList<quint16> val; //Data value
  quint16 temp;

  QDataStream mbStream(mbData);
  mbStream >> byteCount;
  for (int loop=0; loop < (byteCount/2); ++loop) {
    mbStream >> temp; // Extract a word from the data
    val.append(temp); // Append it to the QList
  }

  //  qDebug() << "rx4r-> bytes:" << byteCount << ", val:" << val;
  return(val); //Modbus data
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 0x06 WriteSingleRegister
QByteArray ZModbus::tx06(quint16 tid, quint16 addr, quint16 val)
{
  QByteArray tcpFrame = tx6W(tid, FC_06, addr, val);
  return(tcpFrame); // TCP frame for transmission
}

bool ZModbus::rx06(QByteArray &mbData)
{
  quint8 addr; //Count of how many data bytes in recieved frame
  quint16 val; //Data value

  QDataStream mbStream(mbData);
  mbStream >> addr >> val;
  //  qDebug() << "rx4w-> 1 byte:" << byteCount << ", val:" << val ;
  return(val); // Modbus data
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*
// 0x10 WriteMultipleRegisters
QByteArray ZModbus::tx10(quint16 tid, quint16 addr, QList<quint16> val)
{

}

bool ZModbus::rx10(QByteArray &mbData)
{

}
*/
//##############################################################
//--------------------------------------------------------------
ZModbus::mbReplyType ZModbus::tcpToModbusReply(QByteArray &tcpFrame)
{
  mbReplyType mbData;
  QDataStream stream(tcpFrame);
  quint16 pid; // Protocol identifier (Modbus is always 0x0000).
  quint16 len; // Length of bytes to follow (Repeated in Modbus part of frame as well).
  quint8 uid;  // Unit identifier (Ignored for TCP transactions unless serial tunneling)

  stream >> mbData.tid >> pid >> len >> uid >> mbData.fc;
  mbData.data = tcpFrame.remove(0,8); // Strip off TCP part of frame to leave Modbus frame (minus function code) part only
  //  qDebug() << "tcpFrame-> tid:"<< mbData.tid<<", pid:"<<pid<<", length:"<<len<<", uid:"<< uid<< ", mbData.fc:"<< fc<<", mbData->"<< mbData.data.toHex();
  return(mbData);  // Reply with modbus part of transaction
}

