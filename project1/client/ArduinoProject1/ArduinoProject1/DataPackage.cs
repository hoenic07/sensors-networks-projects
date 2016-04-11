using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public class DataPackage
    {
        public static float GetValue(ArduinoMessage msg)
        {
            var data = msg.Data;
            if (data == null || data.Length != 1) throw new ArgumentException("Input array must have exactly one value!");
            return ShortToFloat(data[0]);
        }

        public static KeyValuePackage GetKeyValuePackage(ArduinoMessage msg)
        {
            var data = msg.Data;
            if (data == null || data.Length != 2) throw new ArgumentException("Input array must have exactly two values!");
            var para = (Parameter)data[0];
            var value = ShortToFloat(data[1]);
            return new KeyValuePackage { Parameter = para, Value = value };
        }

        public static short[] ToValueArray(Parameter param, float value)
        {
            return new short[] { (short)param, FloatToShort(value) };
        }

        private static float ShortToFloat(short value)
        {
            return value / 100f;
        }

        private static short FloatToShort(float value)
        {
            return (short)(value * 100);
        }
        
    }

    public class KeyValuePackage
    {
        public Parameter Parameter { get; set; }
        public float Value { get; set; }
    }
}
