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
        ALARM_ACC = 19,
        RESET_MINMAX = 20,
        ACK = 21,
        NACK = 22,
        INVALID = 23 // will not be sent or received from sensor. Just used when message has invalid start/end bytes or invalid length.
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
        EMPTY = 0,
        VAL = 1, // e.g. RESP_TEMP
        PARAM =2, // REQ_PARA
        PARAM_VAL = 3, // RES_PARA
    }

}
