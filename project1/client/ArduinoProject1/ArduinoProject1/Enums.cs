using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public enum Command
    {
        REQ_ACK = 102,
        REQ_TEMP = 10,
        RESP_TEMP = 11,
        REQ_X = 20,
        REQ_Y = 21,
        REQ_Z = 22,
        RESP_X = 30,
        RESP_Y = 31,
        RESP_Z = 32,
        REQ_PARA = 40,
        RESP_PARA = 41,
        SET_PARA = 42,
        ALARM_TEMP = 50,
        ALARM_X = 60,
        ALARM_Y = 61,
        ALARM_Z = 62,
        RESET_MINMAX = 70,
        ACK = 100,
        NACK = 101,
        INVALID = 103 // will not be sent or received from sensor. Just used when message has invalid start/end bytes or invalid length.
    }

    public enum Parameter
    {
        UPPER_TEMP_THRESHOLD = 1,
        LOWER_TEMP_THRESHOLD = 2,
        TEMP_PER_TIME_THRESHOLD = 3,
        TOTAL_ACC_THRESHOLD = 4,
        MAX_TEMP = 5,
        MIN_TEMP = 6,
        MAX_ACC_X = 7,
        MAX_ACC_Y = 8,
        MAX_ACC_Z = 9,
        TEMP_UPDATE_INTERVAL = 10,
        TEMP_UPDATE_DELTA = 11,
        CALIBRATION_TEMP = 12,
        CALIBRATION_MIN_X = 13,
        CALIBRATION_MAX_X = 14,
        CALIBRATION_MIN_Y = 15,
        CALIBRATION_MAX_Y = 16,
        CALIBRATION_MIN_Z = 17,
        CALIBRATION_MAX_Z = 18,
    }

    public enum Receiver
    {
        BUS = 1,
        SENSOR = 2
    }

    public enum DataFormat
    {
        NO_DATA = 1,
        VALUE = 2, // e.g. RESP_TEMP
        PARAMETER =3, // REQ_PARA
        PARAMETER_AND_VALUE = 4, // RES_PARA
    }

}
