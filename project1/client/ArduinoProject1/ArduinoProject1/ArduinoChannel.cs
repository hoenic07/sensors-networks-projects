using System;
using System.Diagnostics;
using System.IO.Ports;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public delegate void MessageReceivedHandler(ArduinoMessage message);

    public class ArduinoChannel
    {
        private SerialPort _port;
        private bool _performClose;
        public event MessageReceivedHandler MessageReceived;

        public ArduinoChannel()
        {
            _port = new SerialPort("COM3");
            _port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
        }

        public void Open()
        {
            if (_port.IsOpen)
            {
                return;
            }
            _port.Open();

            //TODO handle the result in DataReceivedHandler or use a queue? state machine?
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
            if (_port.IsOpen)
            {
                _port.Close();
            }
        }

        public void SendMessage(ArduinoMessage msg)
        {
            var bytes = msg.ToBytes();
            _port.Write(bytes, 0, bytes.Length);
        }


        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;

            byte[] result = new byte[sp.BytesToRead];

            sp.Read(result, 0, result.Length);

            //lock to make sure that the data are added in the correct order
            /*lock (_messageQueue)
            {
                foreach (byte b in result)
                {
                    _messageQueue.Push(b);
                }
            }*/
        }
    }
}
