using System;
using System.Diagnostics;
using System.IO.Ports;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public delegate void MessageReceivedHandler(ArduinoMessage message);
    public delegate void MessageLoggedHandler(ArduinoMessage message);

    public class ArduinoChannel
    {
        private SerialPort _port;
        private bool _performClose;
        public event MessageReceivedHandler MessageReceived;
        public Queue<AwaitingMessage> _messageQueue;
        public event MessageLoggedHandler MessageLogged;

        public ArduinoChannel()
        {
            _port = new SerialPort("COM3");
            _port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
            _messageQueue = new Queue<AwaitingMessage>();
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

                            //process the message, either send received handler or continue awaited message
                            ProcessReceivedMessage(message);
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

        private void ProcessReceivedMessage(ArduinoMessage message)
        {
            LogMessage(message);
            var pendingResp = _messageQueue.Peek();
            if (message.Command == pendingResp.ExceptedResponseCommand || message.Command == Command.NACK)
            {
                _messageQueue.Dequeue();
                pendingResp.Action(message);
            }
            else if (MessageReceived != null)
            {
                MessageReceived(message);
            }
        }

        public void Close()
        {
            if (_port.IsOpen)
            {
                _port.Close();
            }
        }

        public Task<ArduinoMessage> SendMessageAsync(Command cmd)
        {
            return SendMessageAsync(new ArduinoMessage(cmd));
        }

        public Task<ArduinoMessage> SendMessageAsync(Command cmd, Parameter param)
        {
            return SendMessageAsync(new ArduinoMessage(cmd, new short[] { (short)param }, DataFormat.PARAMETER));
        }

        public Task<ArduinoMessage> SendMessageAsync(Command cmd, Parameter param, float value)
        {
            return SendMessageAsync(new ArduinoMessage(cmd, DataPackage.ToValueArray(param, value), DataFormat.PARAMETER_AND_VALUE));
        }

        public Task<ArduinoMessage> SendMessageAsync(ArduinoMessage msg)
        {
            LogMessage(msg);

            var bytes = msg.ToBytes();
            _port.Write(bytes, 0, bytes.Length);
            
            var excpectedResponseCmd = Matcher.RequestResponse[msg.Command];

            var tcs = new TaskCompletionSource<ArduinoMessage>();
            var res = new AwaitingMessage
            {
                ExceptedResponseCommand = excpectedResponseCmd,
                Action = (m) =>
                {
                    tcs.TrySetResult(m);
                }
            };

            _messageQueue.Enqueue(res);

            return tcs.Task;
        }

        private void LogMessage(ArduinoMessage msg)
        {
            if (MessageLogged != null) MessageLogged(msg);
        }
    }

    public class AwaitingMessage
    {
        public Command ExceptedResponseCommand { get; set; }

        public Action<ArduinoMessage> Action { get; set; }
    }

}
