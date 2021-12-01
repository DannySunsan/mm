using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace bat
{
    class SystemParameter
    {

        public const string strConfigPath = @"..\common_config\system_config.xml";
        public const string strPostPath = @"\source\_posts";
        public const string strDraftPath = @"\source\_drafts";

        private static SystemParameter _SystemParameter = null;

        static private string blogPath;
        static public string BlogPath()
        {
            return blogPath;
        }
        static public string getPostBlogPath()
        {          
            return blogPath + strPostPath;
        }
        static public string getDraftBlogPath()
        {
            return blogPath + strDraftPath;
        }

        static SystemParameter()
        {
            try
            {
                _SystemParameter = new SystemParameter();

                XmlDocument xml = new XmlDocument();
                xml.Load(strConfigPath);
                XmlNode blog = xml.SelectSingleNode("/root/Project/blog");//查找<blog> 
                blogPath = blog.InnerText;
            }
            catch(Exception e)
            {
                throw e;
            }
        }

        public static SystemParameter getSysParam()
        {
            return _SystemParameter;
        }
    }
}
