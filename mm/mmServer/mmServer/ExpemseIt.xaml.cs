using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
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
    /// ExpemseIt.xaml 的交互逻辑
    /// </summary>
    public partial class ExpemseIt : Page
    {
        public string FilePath
        {
            get{ return (string)GetValue(strFilePath); }
            set => SetValue(strFilePath, value);
        }
        public static readonly DependencyProperty strFilePath =
           DependencyProperty.Register("FilePath",
               typeof(string), typeof(ExpemseIt), new UIPropertyMetadata());

        public ExpemseIt()
        {
            InitializeComponent();
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {           
           expenserportpage expenseReportPage = new expenserportpage(this.peopleListBox.SelectedItem);
           this.NavigationService.Navigate(expenseReportPage);
        }

        private void Button_Click_OpenFile(object sender, RoutedEventArgs e)
        {
            //System.Random rand = new System.Random();
            //_randMV.RandNum = rand.Next(20000).ToString();
            //定义一个文件打开控件
            OpenFileDialog ofd = new OpenFileDialog();
            //设置打开对话框的初始目录，默认目录为exe运行文件所在的路径
            ofd.InitialDirectory = AppDomain.CurrentDomain.BaseDirectory;
            //设置打开对话框的标题
            ofd.Title = "请选择要打开的文件";
            //设置打开对话框可以多选
            ofd.Multiselect = true;
            //设置对话框打开的文件类型
            ofd.Filter = "文本文件|*.xml|所有文件|*.*";
            //设置文件对话框当前选定的筛选器的索引
            ofd.FilterIndex = 0;
            //设置对话框是否记忆之前打开的目录
            ofd.RestoreDirectory = true;
            if (ofd.ShowDialog() == true)
            {
                //获取用户选择的文件完整路径
                FilePath = ofd.FileName;
                //获取对话框中所选文件的文件名和扩展名，文件名不包括路径
                //string fileName = ofd.SafeFileName;
                //using (FileStream fsRead = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.Read))
                //{
                //    //定义二进制数组 22 
                //    byte[] buffer = new byte[1024 * 1024 * 5];
                //    //从流中读取字节
                //    int r = fsRead.Read(buffer, 0, buffer.Length);
                    
                //}
            }
        }       
    }
}
