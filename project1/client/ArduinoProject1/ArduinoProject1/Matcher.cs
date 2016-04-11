using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public static class Matcher
    {
        public static Dictionary<Command, Command> RequestResponse = new Dictionary<Command, Command>
        {
            {Command.REQ_ACK, Command.ACK },
            {Command.REQ_PARA, Command.RESP_PARA },
            {Command.REQ_TEMP, Command.RESP_TEMP },
            {Command.REQ_X, Command.RESP_X },
            {Command.REQ_Y, Command.RESP_Y },
            {Command.REQ_Z, Command.RESP_Z },
            {Command.SET_PARA, Command.ACK },
            {Command.ALARM_TEMP, Command.ACK },
            {Command.ALARM_X, Command.ACK },
            {Command.ALARM_Y, Command.ACK },
            {Command.ALARM_Z, Command.ACK },
            {Command.RESET_MINMAX, Command.ACK },
        };
    }
}
