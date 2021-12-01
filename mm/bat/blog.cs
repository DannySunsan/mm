using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using System.Windows;
namespace bat
{
    public class Blog
    {
        private string name;
        private DateTime crateTime;
        private DateTime modifyTime;
        public struct ProcessParameter
        {
            public string strBlogName;

        };
        public string Name
        {
            set => name = value;
            get { return name;}
        }
        public DateTime CreateTime
        {
            set => crateTime = value;
            get { return crateTime; }
        }
        public DateTime ModifyTime
        {
            set => modifyTime = value;
            get { return modifyTime; }
        }
        public Blog(FileInfo file)
        {
            Name = file.Name;
            CreateTime = file.CreationTime;
            ModifyTime = file.LastWriteTime;
        }

        public bool NewBlog(string strName)
        {
            return Process(strName);

        }

        public bool deleteBlog(string strName)
        {
            return Process(strName);

        }

        public bool Process(string param)
        {
            Process proc = null;
            try
            {
                string blog = SystemParameter.BlogPath();
                string sDisk = blog.Substring(0, 1);
                proc = new Process();
                proc.StartInfo.FileName = @"blog.bat";
                proc.StartInfo.Arguments = sDisk + " " + blog + " " + param;
                proc.StartInfo.CreateNoWindow = true;
                proc.Start();
                proc.WaitForExit();
                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }
        }
    }
}
