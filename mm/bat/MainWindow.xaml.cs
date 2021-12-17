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
using System.Text.RegularExpressions;
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
                    listBlog.Items.Insert(index++, new Blog(file,Blog.eSTATUS.post));
                }
                DirectoryInfo folderDraft = new DirectoryInfo(SystemParameter.getDraftBlogPath());
                foreach (FileInfo file in folderDraft.GetFiles("*.md"))
                {
                    listBlog.Items.Insert(index++, new Blog(file, Blog.eSTATUS.draft));
                    
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
           
        }

        private void OnBnClickNewBlog(object sender, RoutedEventArgs e)
        {
            if (tbBlog.Text.Length!=0)
                BlogManagement.NewBlog(tbBlog.Text);
            else
                MessageBox.Show("新建失败");
        }

        private void OnMouseRightUpListBlog(object sender, MouseButtonEventArgs e)
        {
          
        }

        private void ListBlog_Delete_Click(object sender, RoutedEventArgs e)
        {           
            if (listBlog.SelectedIndex != -1)
            {
                //删除blog
                ListItem item = (ListItem)listBlog.SelectedItem;
                string sName = item.ContentStart.ToString();
                if (BlogManagement.DeleteBlog(sName))
                    onBnClickReloadBlog(sender, e);
                else
                    MessageBox.Show("删除失败");
            }
        }

        private void ListBlogContextOp(object sender, ContextMenuEventArgs e)
        {              
            if (listBlog.SelectedIndex == -1)
            {
                e.Handled = true;
            }
        }

        private void OnMouseDbClickListBlog(object sender, MouseButtonEventArgs e)
        {

        }

        private void tbBlogName_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            if (Regex.IsMatch(e.Text, "(\\\\|\\/|:|\\*|\\?|\"|\\<|\\>)"))
                e.Handled = true;
            else
                e.Handled = false;
        }

        private void tbBlogName_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if ((tbBlog.Text.Length == 0 && e.Key == Key.Space)||
                e.Key == Key.ImeProcessed)
                e.Handled = true;
        }

        private void TbBlog_Pasting(object sender, DataObjectPastingEventArgs e)
        {
            string text = (string)e.DataObject.GetData(typeof(string));
            text = Regex.Replace(text, "(\\\\|\\/|:|\\*|\\?|\"|\\<|\\>)", "");
            e.DataObject.SetData(text);
        }

        private void ListBlog_Pulish_Click(object sender, RoutedEventArgs e)
        {
            if (listBlog.SelectedIndex != -1)
            {
                //发布blog
                var v = listBlog.SelectedItem;
                //ListItem item = (ListItem)listBlog.SelectedItem;
                //string sName = item.ContentStart.ToString();
                //if (BlogManagement.PublishBlog(sName))
                //    onBnClickReloadBlog(sender, e);
                //else
                //    MessageBox.Show("发布失败");
            }
        }

        private void tbBlogName_TextInput(object sender, TextCompositionEventArgs e)
        {
            if (Regex.IsMatch(e.Text, "(\\\\|\\/|:|\\*|\\?|\"|\\<|\\>)"))
                e.Handled = true;
            else
                e.Handled = false;
        }

        private void tbBlogName_KeyDown(object sender, KeyEventArgs e)
        {
            if ((tbBlog.Text.Length == 0 && e.Key == Key.Space) ||
                 e.Key == Key.ImeProcessed)
                e.Handled = true;
        }

        private void tbBlogName_KeyUp(object sender, KeyEventArgs e)
        {
            if ((tbBlog.Text.Length == 0 && e.Key == Key.Space) ||
                 e.Key == Key.ImeProcessed)
                e.Handled = true;
        }

        private void tbBlogName_PreviewKeyUp(object sender, KeyEventArgs e)
        {
            if ((tbBlog.Text.Length == 0 && e.Key == Key.Space) ||
                 e.Key == Key.ImeProcessed)
                e.Handled = true;
        }
    }
}
