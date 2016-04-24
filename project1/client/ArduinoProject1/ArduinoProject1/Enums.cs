using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProject1
{
    public enum Command
    {
        REQ_ACK = 0,
        REQ_TEMP = 1,
        RESP_TEMP = 2,
        REQ_X = 3,
        REQ_Y = 4,
        REQ_Z = 5,
        REQ_PITCH = 6,
        REQ_ROLL = 7,
        REQ_THETA = 8,
        RESP_X = 9,
        RESP_Y = 10,
        RESP_Z = 11,
        RESP_PITCH = 12,
        RESP_ROLL = 13,
        RESP_THETA = 14,
        REQ_PARA = 15,
        RESP_PARA = 16,
        SET_PARA = 17,
        ALARM_TEMP = 18,
        ALARM_X = 19,
        ALARM_Y = 20,
        ALARM_Z = 21,
        RESET_MINMAX = 22,
        ACK = 23,
        NACK = 24,
        INVALID = 25 // will not be sent or received from sensor. Just used when message has invalid start/end bytes or invalid length.
    }

    public enum Parameter
    {
        UPPER_TEMP_THRESHOLD = 0,
        LOWER_TEMP_THRESHOLD = 1,
        TEMP_PER_TIME_THRESHOLD = 2,
        TOTAL_ACC_THRESHOLD = 3,
        MAX_TEMP = 4,
        MIN_TEMP = 5,
        MAX_ACC_X = 6,
        MAX_ACC_Y = 7,
        MAX_ACC_Z = 8,
        TEMP_UPDATE_INTERVAL = 9,
        TEMP_UPDATE_DELTA = 10,
        CALIBRATION_TEMP = 11,
        CALIBRATION_MIN_X = 12,
        CALIBRATION_MAX_X = 13,
        CALIBRATION_MIN_Y = 14,
        CALIBRATION_MAX_Y = 15,
        CALIBRATION_MIN_Z = 16,
        CALIBRATION_MAX_Z = 17,
    }

    public enum Receiver
    {
        BUS = 0,
        SENSOR = 1
    }

    public enum DataFormat
    {
        NO_DATA = 0,
        VALUE = 1, // e.g. RESP_TEMP
        PARAMETER =2, // REQ_PARA
        PARAMETER_AND_VALUE = 3, // RES_PARA
    }

}
