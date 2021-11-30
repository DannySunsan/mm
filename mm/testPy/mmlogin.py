import urllib.request
import urllib.parse
from http import cookiejar

def browser(url,user,passwd):  
    try:
        #获得一个cookieJar实例
        cj = cookiejar.CookieJar()
        #cookieJar作为参数，获得一个opener的实例
        
        opener =urllib.request.build_opener(urllib.request.HTTPCookieProcessor(cj))
        #伪装成一个正常的浏览器，避免有些web服务器拒绝访问。
        opener.addheaders = [('User-agent','Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.45 Safari/537.36'),
        ('Accept','text/html,application/xhtml+xml,application/xml'),
        ('Cookie','JSESSIONID=6F142420AA6D76E7685CA1C99E22A293; kabalainstall=false')]
        #生成Post数据，含有登陆用户名密码。urlencode
        #data = urllib.parse.urlencode({"kass_username_in":user,"kass_password_in":passwd})
        #以post的方法访问登陆页面，访问之后cookieJar会自定保存cookie
        # urllib.request.install_opener(opener)
        # response3=urllib.request.urlopen(url)
        
        #opener.open(login_page,data.encode())
        #cookiejar.FileCookieJar.save('\\cookie')
        # 以带cookie的方式访问页面
        op=opener.open(url)
        # resp = urllib.request.urlopen(url)
        #读取页面源码
        data = op.read().decode('utf-8')
        return data

    except Exception as e:
        print(str(e))