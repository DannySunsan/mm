using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace mmServer
{
    public class RandMV: INotifyPropertyChanged
    {
        private Randam _rd;
        public RandMV()
        {
            _rd = new Randam();
        }
        public string RandNum
        {
            get => _rd.RandNum;
            set
            {
                _rd.RandNum = value;
                RaisePropertyChanged("RandNum");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void RaisePropertyChanged(string proName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(proName));
        }
    }
}
