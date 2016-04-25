using Caliburn.Micro;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ArduinoProject1.ViewModels
{
    public class MainViewModel : PropertyChangedBase
    {
        #region Members

        private ArduinoChannel _channel;

        #endregion

        #region Properties

        public ObservableCollection<LogEntry> LogEntries { get; set; }

        private double _currentTemperatur;

        public double CurrentTemperature
        {
            get { return _currentTemperatur; }
            set { _currentTemperatur = value; NotifyOfPropertyChange(); }
        }

        private double _minMeasuredTemperature;

        public double MinMeasuredTemperature
        {
            get { return _minMeasuredTemperature; }
            set { _minMeasuredTemperature = value; NotifyOfPropertyChange(); }
        }
        private double _maxMeasuredTemperature;

        public double MaxMeasuredTemperature
        {
            get { return _maxMeasuredTemperature; }
            set { _maxMeasuredTemperature = value; NotifyOfPropertyChange(); }
        }

        private double _currentAccX;

        public double CurrentAccX
        {
            get { return _currentAccX; }
            set { _currentAccX = value; NotifyOfPropertyChange(); }
        }

        private double _currentAccY;

        public double CurrentAccY
        {
            get { return _currentAccY; }
            set { _currentAccY = value; NotifyOfPropertyChange(); }
        }

        private double _currentAccZ;

        public double CurrentAccZ
        {
            get { return _currentAccZ; }
            set { _currentAccZ = value; NotifyOfPropertyChange(); }
        }

        private double _pitch;

        public double Pitch
        {
            get { return _pitch; }
            set { _pitch = value; NotifyOfPropertyChange(); }
        }

        private double _roll;

        public double Roll
        {
            get { return _roll; }
            set { _roll = value; NotifyOfPropertyChange(); }
        }

        private double _theta;

        public double Theta
        {
            get { return _theta; }
            set { _theta = value; NotifyOfPropertyChange(); }
        }
        
        private double _maxAccX;

        public double MaxAccX
        {
            get { return _maxAccX; }
            set { _maxAccX = value; NotifyOfPropertyChange(); }
        }

        private double _maxAccY;

        public double MaxAccY
        {
            get { return _maxAccY; }
            set { _maxAccY = value; NotifyOfPropertyChange(); }
        }

        private double _maxAccZ;

        public double MaxAccZ
        {
            get { return _maxAccZ; }
            set { _maxAccZ = value; NotifyOfPropertyChange(); }
        }

        private int _selectedSliderInterval;

        public int SelectedSliderInterval
        {
            get { return _selectedSliderInterval; }
            set { _selectedSliderInterval = value; NotifyOfPropertyChange(); }
        }

        private int _selectedSliderDelta;

        public int SelectedSliderDelta
        {
            get { return _selectedSliderDelta; }
            set { _selectedSliderDelta = value; NotifyOfPropertyChange(); }
        }

        private int _minTempThreshold;

        public int MinTempThreshold
        {
            get { return _minTempThreshold; }
            set { _minTempThreshold = value; NotifyOfPropertyChange(); }
        }

        private int _maxTempThreshold;

        public int MaxTempThreshold
        {
            get { return _maxTempThreshold; }
            set { _maxTempThreshold = value; NotifyOfPropertyChange(); }
        }

        private int _deltaTempThreshold;

        public int DeltaTempThreshold
        {
            get { return _deltaTempThreshold; }
            set { _deltaTempThreshold = value; NotifyOfPropertyChange(); }
        }

        private float _totalAccelerationThreshold;

        public float TotalAccelerationThreshold
        {
            get { return _totalAccelerationThreshold; }
            set { _totalAccelerationThreshold = value; NotifyOfPropertyChange(); }
        }

        private int _selectedCalibrationMetricIndex;

        public int SelectedCalibrationMetricIndex
        {
            get { return _selectedCalibrationMetricIndex; }
            set { _selectedCalibrationMetricIndex = value; NotifyOfPropertyChange(); }
        }

        private float _calibrationValue;

        public float CalibrationValue
        {
            get { return _calibrationValue; }
            set { _calibrationValue = value; NotifyOfPropertyChange(); }
        }

        #endregion

        #region Ctor

        public MainViewModel()
        {
            _channel = new ArduinoChannel();
            _channel.MessageReceived += _channel_MessageReceived;
            _channel.MessageLogged += _channel_MessageLogged;
            LogEntries = new ObservableCollection<LogEntry>();
        }

        #endregion

        #region Actions / Events

        private void _channel_MessageReceived(ArduinoMessage message)
        {
            Execute.BeginOnUIThread(() =>
            {
                switch (message.Command)
                {
                    case Command.RESP_TEMP:
                        CurrentTemperature = DataPackage.GetValue(message);
                        break;
                    case Command.RESP_X:
                        CurrentAccX = DataPackage.GetValue(message);
                        break;
                    case Command.RESP_Y:
                        CurrentAccY = DataPackage.GetValue(message);
                        break;
                    case Command.RESP_Z:
                        CurrentAccZ = DataPackage.GetValue(message);
                        break;
                    case Command.ALARM_TEMP_MIN:
                    case Command.ALARM_TEMP_MAX:
                    case Command.ALARM_TEMP_DT:
                    case Command.ALARM_ACC:
                        MessageBox.Show("Alarm!! " + message.Command);
                        break;
                    default:
                        break;
                }
            });
        }

        private void _channel_MessageLogged(ArduinoMessage message)
        {
            Execute.BeginOnUIThread(() => LogEntries.Add(new LogEntry(message)));
        }

        public async void Connect()
        {
            _channel.Open();
            var res = await _channel.SendMessageAsync(Command.REQ_ACK);
            if (res.Command == Command.ACK)
            {
                MessageBox.Show("Connected!");
            }
        }

        public void Disconnect()
        {
            _channel.Close();
        }

        #region Temp

        public async void GetCurrentTemp()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_TEMP);
            CurrentTemperature = DataPackage.GetValue(res);
        }

        public async void GetMinTemp()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.MIN_TEMP);
            MinMeasuredTemperature = DataPackage.GetKeyValuePackage(res).Value;
        } 

        public async void GetMaxTemp()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.MAX_TEMP);
            MaxMeasuredTemperature = DataPackage.GetKeyValuePackage(res).Value;
        }

        #endregion

        #region Acceleration

        public async void GetCurrentAccX()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_X);
            CurrentAccX = DataPackage.GetValue(res);
        }

        public async void GetCurrentAccY()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_Y);
            CurrentAccY = DataPackage.GetValue(res);
        }

        public async void GetCurrentAccZ()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_Z);
            CurrentAccZ = DataPackage.GetValue(res);
        }

        public async void GetMaxAccX()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.MAX_ACC_X);
            MaxAccX = DataPackage.GetKeyValuePackage(res).Value;
        }

        public async void GetMaxAccY()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.MAX_ACC_Y);
            MaxAccY = DataPackage.GetKeyValuePackage(res).Value;
        }

        public async void GetMaxAccZ()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.MAX_ACC_Z);
            MaxAccZ = DataPackage.GetKeyValuePackage(res).Value;
        }

        public async void GetPitch()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_PITCH);
            Pitch = DataPackage.GetValue(res);
        }

        public async void GetRoll()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_ROLL);
            Roll = DataPackage.GetValue(res);
        }

        public async void GetTheta()
        {
            var res = await _channel.SendMessageAsync(Command.REQ_THETA);
            Theta = DataPackage.GetValue(res);
        }

        #endregion

        #region Auto Update

        public async void SetAutoUpdateDeltaTemp()
        {
            await _channel.SendMessageAsync(Command.SET_PARA, Parameter.TEMP_UPDATE_DELTA, SelectedSliderDelta);
        }

        public async void SetAutoUpdateIntervalTemp()
        {
            await _channel.SendMessageAsync(Command.SET_PARA, Parameter.TEMP_UPDATE_INTERVAL, SelectedSliderInterval);
        }

        #endregion

        #region Thresholds

        public async void GetThresholds()
        {
            var res1 = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.LOWER_TEMP_THRESHOLD);
            MinTempThreshold = (int)DataPackage.GetKeyValuePackage(res1).Value;
            var res2 = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.UPPER_TEMP_THRESHOLD);
            MaxTempThreshold = (int)DataPackage.GetKeyValuePackage(res2).Value;
            var res3 = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.TEMP_PER_TIME_THRESHOLD);
            DeltaTempThreshold = (int)DataPackage.GetKeyValuePackage(res3).Value;
            var res4 = await _channel.SendMessageAsync(Command.REQ_PARA, Parameter.TOTAL_ACC_THRESHOLD);
            TotalAccelerationThreshold = (int)DataPackage.GetKeyValuePackage(res4).Value;
        }

        public async void SetThresholds()
        {
            await _channel.SendMessageAsync(Command.SET_PARA, Parameter.LOWER_TEMP_THRESHOLD, MinTempThreshold);
            await _channel.SendMessageAsync(Command.SET_PARA, Parameter.UPPER_TEMP_THRESHOLD, MinTempThreshold);
            await _channel.SendMessageAsync(Command.SET_PARA, Parameter.TEMP_PER_TIME_THRESHOLD, DeltaTempThreshold);
            await _channel.SendMessageAsync(Command.SET_PARA, Parameter.TOTAL_ACC_THRESHOLD, TotalAccelerationThreshold);
        }

        #endregion

        #region Log / Reset / Calibration

        public void ResetMinMax()
        {
            _channel.SendMessageAsync(Command.RESET_MINMAX);
        }

        public void ClearLog()
        {
            LogEntries.Clear();
        }

        public void SetCalibration()
        {
            Parameter param = Parameter.CALIBRATION_TEMP;
            switch (SelectedCalibrationMetricIndex)
            {
                case 0:
                    param = Parameter.CALIBRATION_MIN_X;
                    break;
                case 1:
                    param = Parameter.CALIBRATION_MAX_X;
                    break;
                case 2:
                    param = Parameter.CALIBRATION_MIN_Y;
                    break;
                case 3:
                    param = Parameter.CALIBRATION_MAX_Y;
                    break;
                case 4:
                    param = Parameter.CALIBRATION_MIN_Z;
                    break;
                case 5:
                    param = Parameter.CALIBRATION_MAX_Z;
                    break;
                case 6:
                    param = Parameter.CALIBRATION_TEMP;
                    break;
                default:
                    break;
            }

            _channel.SendMessageAsync(Command.SET_PARA, param, CalibrationValue);

        }

        #endregion

        #endregion
    }
}
