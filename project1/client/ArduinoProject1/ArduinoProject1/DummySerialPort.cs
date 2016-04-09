using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    /// <summary>
    /// Simulate the communication to the arduino
    /// </summary>
    public class DummySerialPort
    {
        private Queue<byte> _messageQueue;

        private byte[] _dummyBytes = new byte[] { 10, 5, Constants.MESSAGE_START_BYTE, 6, (byte)Receiver.BUS, (byte)Command.ACK, (byte)DataFormat.NO_DATA, Constants.MESSAGE_END_BYTE, 0, 0, 0 };

        public DummySerialPort()
        {
            _messageQueue = new Queue<byte>();
        }

        public void Open()
        {
            Task.Run(async () =>
            {
                foreach (var b in _dummyBytes)
                {
                    _messageQueue.Enqueue(b);
                    await Task.Delay(100);
                }
            });
        }

        public void Close() { }

        public int ReadByte()
        {
            while (_messageQueue.Count == 0) Thread.Sleep(10) ;
            return _messageQueue.Dequeue();
        }

        public void Read(byte[] bytes, int offset, int count)
        {
            for (int i = 0; i < count; i++)
            {
                while (_messageQueue.Count == 0) Thread.Sleep(10);
                bytes[offset + i] = _messageQueue.Dequeue();
            }
        }

        public void Write(byte[] bytes, int offset, int count) { }
    }
}
