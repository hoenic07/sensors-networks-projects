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
            {Command.REQ_PITCH, Command.RESP_PITCH },
            {Command.REQ_ROLL, Command.RESP_ROLL },
            {Command.REQ_THETA, Command.RESP_THETA },
            {Command.SET_PARA, Command.ACK },
            {Command.ALARM_TEMP_MAX, Command.ACK },
            {Command.ALARM_TEMP_MIN, Command.ACK },
            {Command.ALARM_TEMP_DT, Command.ACK },
            {Command.ALARM_ACC, Command.ACK },
            {Command.RESET_MINMAX, Command.ACK },
        };
    }
}
