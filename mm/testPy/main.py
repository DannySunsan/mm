
from mmlogin import *

def main():
    host = "http://doc.united-imaging.com"
    login_page = "/kass/basic/login/page_login.jsp"
    doc_page = "/kass/basic/main/kwin.jsp"
    foldtree = '/kass/basic/file/foldtree/page_foldtree.jsp' 
    data = browser(host+foldtree,'yongquan.sun','Syq008753..')
    print(str(data))
if __name__ == "__main__":
    main()

