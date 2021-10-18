using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace mmServer
{
    /// <summary>
    /// expenserportpage.xaml 的交互逻辑
    /// </summary>
    public partial class expenserportpage : Page
    {
        public expenserportpage()
        {
            InitializeComponent();
        }
        // Custom constructor to pass expense report data
        public expenserportpage(object data) : this()
        {
            // Bind to expense report data.
            this.DataContext = data;
        }
    }
}
