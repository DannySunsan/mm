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

namespace bat
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            new SystemParameter();
        }

        private void onBnClickReloadBlog(object sender, RoutedEventArgs e)
        {
            try
            {
                DirectoryInfo folder = new DirectoryInfo(SystemParameter.getPostBlogPath());
                listBlog.Items.Clear();
                int index = 0;
                foreach (FileInfo file in folder.GetFiles("*.md"))
                {
                    listBlog.Items.Insert(index, new Blog(file));
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
           
        }

        private void OnBnClickNewBlog(object sender, RoutedEventArgs e)
        {
            
        }

        private void OnMouseRightUpListBlog(object sender, MouseButtonEventArgs e)
        {
          
        }

        private void ListBlog_Delete_Click(object sender, RoutedEventArgs e)
        {           
            if (listBlog.SelectedIndex != -1)
            {
                listBlog.Items.Remove(listBlog.SelectedItem);
            }
        }

        private void ListBlogContextOp(object sender, ContextMenuEventArgs e)
        {
               
            if (listBlog.SelectedIndex == -1)
            {
                e.Handled = true;
            }
        }
    }
}
