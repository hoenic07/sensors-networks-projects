using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public class ArduinoMessage
    {
        public ArduinoMessage()
        {
            IsValid = true;
        }

        #region Static Method Ctors
        public static ArduinoMessage AsEmptyMessage(Command cmd)
        {
            return new ArduinoMessage
            {
                Command = cmd,
                Format = DataFormat.NO_DATA,
                Data = new short[0]
            };
        }

        public static ArduinoMessage AsValueMessage(Command cmd, short value)
        {
            return new ArduinoMessage
            {
                Command = cmd,
                Format = DataFormat.VALUE,
                Data = new short[] { value }
            };
        }

        #endregion

        #region Properties

        public Command Command { get; private set; }

        public DataFormat Format { get; private set; }

        public short[] Data { get; private set; }

        public bool IsValid { get; private set; }

        #endregion

        #region Methods

        public byte[] ToBytes()
        {
            var list = new List<byte> {
                Constants.MESSAGE_START_BYTE,
                0, // dummy value, will be replaced below
                (byte)Receiver.SENSOR,
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
