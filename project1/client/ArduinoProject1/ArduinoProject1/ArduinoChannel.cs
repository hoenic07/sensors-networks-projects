using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public delegate void MessageReceivedHandler(ArduinoMessage message);

    public class ArduinoChannel
    {
        private DummySerialPort _port;
        private bool _performClose;
        public event MessageReceivedHandler MessageReceived;


        public ArduinoChannel()
        {
            _port = new DummySerialPort(); //TODO: Set correct port here
        }

        public void Open()
        {
            _port.Open();
            Task.Run(() =>
            {
                while (!_performClose)
                {
                    try
                    {
                        var incomingValue = _port.ReadByte();
                        if(incomingValue == Constants.MESSAGE_START_BYTE)
                        {
                            //start byte received. construct message
                            var length = _port.ReadByte();
                            var messageBytes = new byte[length];
                            messageBytes[0] = (byte)incomingValue;
                            messageBytes[1] = (byte)length;
                            _port.Read(messageBytes, 2, messageBytes.Length - 2);
                            var message = new ArduinoMessage();
                            message.FromBytes(messageBytes);

                            //continue if the message is invalid
                            if (!message.IsValid) continue;

                            //send message to listeners
                            if (MessageReceived != null) MessageReceived(message);
                        }
                    }
                    catch(Exception ex)
                    {
                        Debug.WriteLine("Channel > Exception while receiving data!");
                    }
                }

                //reset close flag
                _performClose = false;
            });
        }

        public void Close()
        {
            _performClose = true;
            _port.Close();
        }

        public void SendMessage(ArduinoMessage msg)
        {
            var bytes = msg.ToBytes();
            _port.Write(bytes, 0, bytes.Length);
        }


    }
}
