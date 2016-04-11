using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public class LogEntry
    {
        public DateTime Date { get; set; }

        public string DateFormat
        {
            get { return Date.ToString("HH:mm:ss"); }
        }

        public string Text { get; set; }

        public LogEntry(ArduinoMessage msg)
        {
            Date = DateTime.Now;
            Text = $"{msg.Receiver} {msg.Command} {msg.Format} ";

            switch (msg.Format)
            {
                case DataFormat.NO_DATA:
                    break;
                case DataFormat.VALUE:
                    Text += DataPackage.GetValue(msg);
                    break;
                case DataFormat.PARAMETER:
                    Text += (Parameter)msg.Data[0];
                    break;
                case DataFormat.PARAMETER_AND_VALUE:
                    var kv = DataPackage.GetKeyValuePackage(msg);
                    Text += kv.Parameter + " " + kv.Value;
                    break;
                default:
                    break;
            }
        }

    }
}
