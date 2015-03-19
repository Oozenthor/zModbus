#ifndef ZMODBUS_H
#define ZMODBUS_H

//##############################################################
// Modbus function code defines
//--------------------------------------------------------------
// 0xxxx Discrete Outputs
#define FC_01 (quint8)0x01 // Read Coils
#define FC_05 (quint8)0x05 // Write Single Coil
#define FC_0F (quint8)0x0F // Write Multiple Coils
//--------------------------------------------------------------
// 1xxxx Discrete Inputs
#define FC_02 (quint8)0x02 // Read Discrete Inputs
//--------------------------------------------------------------
// 3xxxx Input Registers
// 0x04 ReadInputRegisters
#define FC_04 (quint8)0x04 // Read Input Registers
//--------------------------------------------------------------
// 4xxxx Holding Registers
#define FC_03 (quint8)0x03 // Read Holding Registers
#define FC_06 (quint8)0x06 // Write Single Register
#define FC_10 (quint8)0x10 // Write Multiple Registers

//##############################################################
// Other Modbus constants
#define PID (quint16)0     // Protocol identifier (always 0 for Modbus)
#define UID (quint8)0xFF   // Unit identifier (0xFF for tcp transactions is reccomended)

//##############################################################
#include <QBitArray>
#include <QList>
#include <QByteArray>
#include <QDataStream>

#include <QTcpSocket>

#include <QDebug>

//##############################################################
class ZModbus : public QObject
{
  Q_OBJECT

public:
  explicit ZModbus(QWidget *parent = 0);
  ~ZModbus();
  //##############################################################
  // Public functions
  //--------------------------------------------------------------
  // 0xxxx Discrete Outputs
  // 0x01 ReadCoils
  /*
  QBitArray ReadCoils(quint16 addr, quint16 qty);
  // 0x05 WriteSingleCoil
  bool WriteSingleCoil(quint16 addr, bool val);
  // 0x0F WriteMultipleCoils
  bool WriteMultipleCoils(quint16 addr, QList<bool> val);

  //--------------------------------------------------------------
  // 1xxxx Discrete Inputs
  // 0x02 ReadDiscreteInputs
  QBitArray ReadDiscreteInputs(quint16 addr, quint16 qty);

  //--------------------------------------------------------------
  // 3xxxx Input Registers
  // 0x04 ReadInputRegisters
  QList<quint16> ReadInputRegisters(quint16 addr, quint16 qty);
*/
  //--------------------------------------------------------------
  // 4xxxx Holding Registers
  // 0x03 ReadHoldingRegisters
  QList<quint16> ReadHoldingRegisters(quint16 addr, quint16 qty);
  // 0x06 WriteSingleRegister
  bool WriteSingleRegister(quint16 addr, quint16 val);
  // 0x10 WriteMultipleRegisters
  bool WriteMultipleRegisters(quint16 addr, quint16 val);
  //--------------------------------------------------------------
  //##############################################################

private:
  QTcpSocket *tcpSocket;
  void mbRead();
  void mbWrite();

  struct mbReplyType {
      quint16 tid;  // Transaction identifier
      qint8 fc;     // Reply Function code
      QByteArray data; // Data part of modbus frame
  };

  //##############################################################
  // Private functions
  //--------------------------------------------------------------
  // Recieved TCP frame to Modbus conversion
  mbReplyType tcpToModbusReply(QByteArray &tcpFrame); // Convert TCP frames to modbus and return data parts

  // 6 word size requests
  QByteArray tx6W(quint16 tid, quint8 fc, quint16 addr, quint16 data); // request a quantity of words

  //##############################################################
  // Modbus Function code implementation
  // tx commands will create a QByteArray suitable to transmit a QTcpSocket->write(QByteArray)
  //  function in a Modbus format
  // rx commands will return data recieved from a QTcpSocket->readAll() event for the matching
  //  transmission identifiers sent from the tx command
  //--------------------------------------------------------------
  // 0xxxx Discrete Outputs
  // 0x01 ReadCoils
  /*
  QByteArray tx01(quint16 tid, quint16 addr, quint16 qty); // request
  QBitArray rx01(QByteArray &mbData); // reply with quantity of values
  // 0x05 WriteSingleCoil
  QByteArray tx05(quint16 tid, quint16 addr, bool val); // request
  bool rx05(QByteArray &mbData); // reply with error status
  // 0x0F WriteMultipleCoils
  QByteArray tx0F(quint16 tid, quint16 addr, QList<bool> val); // request
  bool rx0F(QByteArray &mbData); // reply with error status

  //--------------------------------------------------------------
  // 1xxxx Discrete Inputs
  // 0x02 ReadDiscreteInputs
  QByteArray tx02(quint16 tid, quint16 addr, quint16 qty); // request
  QBitArray rx02(QByteArray &mbData); // reply with quantity of values

  //--------------------------------------------------------------
  // 3xxxx Input Registers
  // 0x04 ReadInputRegisters
  QByteArray tx04(quint16 tid, quint16 addr, quint16 qty); // request
  QList<quint16> rx04(QByteArray &mbData); // reply with quantity of values
*/
  //--------------------------------------------------------------
  // 4xxxx Holding Registers
  // 0x03 ReadHoldingRegisters
  QByteArray tx03(quint16 tid, quint16 addr, quint16 qty); // request
  QList<quint16> rx03(QByteArray &mbData); // reply with quantity of values
  // 0x06 WriteSingleRegister
  QByteArray tx06(quint16 tid, quint16 addr, quint16 val); // request
  bool rx06(QByteArray &mbData); // reply with error status
  // 0x10 WriteMultipleRegisters
//  QByteArray tx10(quint16 tid, quint16 addr, QList<quint16> val); // request
//  bool rx10(QByteArray &mbData); // reply with error status
  //##############################################################
};

#endif // ZMODBUS_H
