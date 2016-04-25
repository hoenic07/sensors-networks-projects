using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public class ArduinoMessage
    {
        #region Ctor

        public ArduinoMessage()
        {
            IsValid = true;
            Receiver = Receiver.BUS;
        }

        public ArduinoMessage(Command cmd)
            :base()
        {
            Command = cmd;
            Format = DataFormat.EMPTY;
            Data = new short[0];
            Receiver = Receiver.SENSOR;
        }

        public ArduinoMessage(Command cmd, short[] data, DataFormat format)
            :base()
        {
            Command = cmd;
            Format = format;
            Data = data;
            Receiver = Receiver.SENSOR;
        }

        #endregion

        #region Properties

        public Command Command { get; private set; }

        public DataFormat Format { get; private set; }

        public short[] Data { get; private set; }

        public bool IsValid { get; private set; }

        public Receiver Receiver { get; set; }

        #endregion

        #region Methods

        public byte[] ToBytes()
        {
            var list = new List<byte> {
                Constants.MESSAGE_START_BYTE,
                0, // dummy value, will be replaced below
                (byte)Receiver,
                (byte)Command,
                (byte)Format };

            foreach (var value in Data)
            {
                list.AddRange(BitConverter.GetBytes(value));
            }

            list.Add(Constants.MESSAGE_END_BYTE);
            list[1] = (byte)list.Count;
            return list.ToArray();
        }

        public void FromBytes(byte[] bytes)
        {
            //check if message is valid first
            if (bytes == null || bytes.Length < 6)
            {
                IsValid = false;
                return;
            }

            var lengthAccordingMessage = bytes[1];
            var receiver = (Receiver)bytes[2];
            if (lengthAccordingMessage != bytes.Length || 
                bytes[0] != Constants.MESSAGE_START_BYTE || 
                bytes[bytes.Length - 1] != Constants.MESSAGE_END_BYTE || 
                receiver != Receiver.BUS)
            {
                IsValid = false;
                return;
            }

            //read command and data format
            Command = (Command)bytes[3];
            Format = (DataFormat)bytes[4];

            //check if datalength is valid
            var dataLength = lengthAccordingMessage - 6;
            if (dataLength % 2 != 0)
            {
                IsValid = false;
                return;
            }

            //read the data
            Data = new short[dataLength / 2];
            for (int i = 0; i < Data.Length; i++)
            {
                Data[i] = BitConverter.ToInt16(bytes, 5 + i * 2);
            }
        }

        #endregion

    }
}
