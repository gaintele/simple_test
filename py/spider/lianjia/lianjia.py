#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
@author: 冰蓝
@site: http://lanbing510.info
"""

import re
import urllib2  
import sqlite3
import random
import threading
from bs4 import BeautifulSoup

import sys
reload(sys)
sys.setdefaultencoding("utf-8")

#登录，不登录不能爬取三个月之内的数据,代码参考博客[1]
#import LianJiaLogIn

#Some User Agents
hds=[{'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 6.2) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.12 Safari/535.11'},\
     {'User-Agent':'Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; Trident/6.0)'},\
     {'User-Agent':'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:34.0) Gecko/20100101 Firefox/34.0'},\
     {'User-Agent':'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_8; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50'},\
     {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50'},\
     {'User-Agent':'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0'},\
     {'User-Agent':'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:2.0.1) Gecko/20100101 Firefox/4.0.1'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; rv:2.0.1) Gecko/20100101 Firefox/4.0.1'},\
     {'User-Agent':'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_0) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11'},\
     {'User-Agent':'Opera/9.80 (Macintosh; Intel Mac OS X 10.6.8; U; en) Presto/2.8.131 Version/11.11'},\
     {'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/44.0.2403.89 Chrome/44.0.2403.89 Safari/537.36'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36 OPR/26.0.1656.60'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 5.1; U; en; rv:1.8.1) Gecko/20061208 Firefox/2.0.0 Opera 9.50'},\
     {'User-Agent':'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; en) Opera 9.50'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:34.0) Gecko/20100101 Firefox/34.0'},\
     {'User-Agent':'Mozilla/5.0 (X11; U; Linux x86_64; zh-CN; rv:1.9.2.10) Gecko/20100922 Ubuntu/10.10 (maverick) Firefox/3.6.10'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/534.57.2 (KHTML, like Gecko) Version/5.1.7 Safari/534.57.2'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36'},\
     {'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11'},\
     {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.16 (KHTML, like Gecko) Chrome/10.0.648.133 Safari/534.16'},\
     {'User-Agent':'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_8; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50'},\
     {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50'},\
     {'User-Agent':'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0'},\
     {'User-Agent':'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)'},\
     {'User-Agent':'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.75 Safari/537.36'},\
     {'User-Agent':'Opera/9.80 (Windows NT 6.1; U; en) Presto/2.8.131 Version/11.11'}]


#北京区域列表
#regions=[u"东城",u"西城",u"朝阳",u"海淀",u"丰台",u"石景山","通州",u"昌平",u"大兴",u"亦庄开发区",u"顺义",u"房山",u"门头沟",u"平谷",u"怀柔",u"密云",u"延庆",u"燕郊"]
regions=["dongcheng","xicheng","chaoyang","haidian","fengtai","shijingshan","tongzhou","changping","daxing","yizhuangkaifaqu","shunyi","fangshan","mentougou","pinggu","huairou","miyun","yanqing","yanjiao"]


lock = threading.Lock()

class SQLiteWraper(object):
    """
    数据库的一个小封装，更好的处理多线程写入
    """
    def __init__(self,path,command='',*args,**kwargs):  
        self.lock = threading.RLock() #锁  
        self.path = path #数据库连接参数  

        if command!='':
            conn=self.get_conn()
            cu=conn.cursor()
            cu.execute(command)

    def get_conn(self):  
        conn = sqlite3.connect(self.path)#,check_same_thread=False)  
        conn.text_factory=str
        return conn   

    def conn_close(self,conn=None):  
        conn.close()  

    def conn_trans(func):  
        def connection(self,*args,**kwargs):  
            self.lock.acquire()  
            conn = self.get_conn()  
            kwargs['conn'] = conn  
            rs = func(self,*args,**kwargs)  
            self.conn_close(conn)  
            self.lock.release()  
            return rs  
        return connection  


    @conn_trans    
    def execute(self,command,method_flag=0,conn=None):  
        cu = conn.cursor()
        try:
            if not method_flag:
                cu.execute(command)
            else:
                cu.execute(command[0],command[1])
            conn.commit()
        except sqlite3.IntegrityError,e:
            print e
            return -1
        except Exception, e:
            print e
            return -2
        return 0

    @conn_trans
    def fetchall(self,command="select community_id from xiaoqu",conn=None):
        cu=conn.cursor()
        lists=[]
        try:
            cu.execute(command)
            lists=cu.fetchall()
        except Exception,e:
            print e
            pass
        return lists    


def gen_xiaoqu_insert_command(info_dict):
    """
    生成小区数据库插入命令
    """
    info_list=[u'community_id',u'community_name',u'district',u'bizcircle',u'building_type',u'build_time',u'avg_price',u'stock',u'url']
    t=[]
    for il in info_list:
        if il in info_dict:
            t.append(info_dict[il])
        else:
            t.append('')
    t=tuple(t)
    command=(r"insert into xiaoqu values(?,?,?,?,?,?,?,?,?)",t)
    return command

def gen_chengjiao_insert_command(info_dict):
    """
    生成成交记录数据库插入命令
    """
    info_list=[u'house_id', u'community_id', u'community_name', u'room_num', u'area', u'direction', u'decorator', u'dealtime', u'total_price', u'floor', u'agent', u'unit_price', u'house_type', u'school_type', u'subway_type']
    t=[]
    for il in info_list:
        if il in info_dict:
            t.append(info_dict[il])
        else:
            t.append('')
    t=tuple(t)
    command=(r"insert into chengjiao values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",t)
    return command

def xiaoqu_spider(db_xq,url_page=u"http://bj.lianjia.com/xiaoqu/1111027375142/"):
    """
    爬取页面链接中的小区信息
    """

    try:
        req = urllib2.Request(url_page,headers=hds[random.randint(0,len(hds)-1)])
        source_code = urllib2.urlopen(req,timeout=10).read()
        plain_text=unicode(source_code)#,errors='ignore')   
        soup = BeautifulSoup(plain_text)
    except (urllib2.HTTPError, urllib2.URLError), e:
        print e
        exit(-1)
    except Exception,e:
        print e
        exit(-1)

    print " %s" % url_page
#    print plain_text
    xiaoqu_list=soup.findAll('li',{'class':'clear xiaoquListItem'})
    for xq in xiaoqu_list:
        info_dict={}
        xq_url = xq.find('a').get('href')
        posinfo = xq.find('div', {'class':'positionInfo'}).text.split('\n')
        if len(posinfo) != 7:
            print "Error! parsing positionInfo fail in xiaoqu %s in region page %s" % (xq_url, url_page)
            continue

        seg = xq_url.strip().split('/')
        if len(seg) != 6:
            print "Error! parsing xiaoquid fail in xiaoqu %s in region page %s" % (xq_url, url_page)
            continue

        xq_id = seg[4]
        xq_name = xq.find('div', {'class':'title'}).text.strip()
        district = posinfo[2].strip()
        bizcircle = posinfo[3].strip()
        style = posinfo[4].strip()
        age = posinfo[5].strip() 
        price = xq.find('div', {'class':'xiaoquListItemPrice'}).span.string
        stock = xq.find('div', {'class':'xiaoquListItemSellCount'}).span.string

        print "     %s %s %s %s %s %s %s %s %s" % (xq_id, xq_name, district, bizcircle, style, age, price, stock, xq_url)

        info_dict.update({u'community_id':xq_id})
        info_dict.update({u'community_name':xq_name})
        info_dict.update({u'district':district})
        info_dict.update({u'bizcircle':bizcircle})
        info_dict.update({u'building_type':style})
        info_dict.update({u'build_time':age})
        info_dict.update({u'avg_price':price})
        info_dict.update({u'stock':stock})
        info_dict.update({u'url':xq_url})

        command=gen_xiaoqu_insert_command(info_dict)
        db_xq.execute(command,1)


def do_xiaoqu_spider(db_xq,region="dongcheng"):
    """
    爬取大区域中的所有小区信息
    """
    url=u"http://bj.lianjia.com/xiaoqu/"+region+"/"
    try:
        req = urllib2.Request(url,headers=hds[random.randint(0,len(hds)-1)])
        source_code = urllib2.urlopen(req,timeout=5).read()
        plain_text=unicode(source_code)#,errors='ignore')   
        soup = BeautifulSoup(plain_text)
    except (urllib2.HTTPError, urllib2.URLError), e:
        print e
        exit(-1)
    except Exception,e:
        print e
        exit(-1)
    d="d="+soup.find('div',{'class':'page-box house-lst-page-box'}).get('page-data')
    exec(d)
    total_pages=d['totalPage']
    print '%s : total_pages %d' % (region, total_pages)

    threads=[]
    for i in range(total_pages):
        url_page=u"http://bj.lianjia.com/xiaoqu/%s/pg%d" % (region, i+1)
#        xiaoqu_spider(db_xq, url_page)
        t=threading.Thread(target=xiaoqu_spider,args=(db_xq,url_page))
        threads.append(t)
    for t in threads:
        t.start()
    for t in threads:
        t.join()

def chengjiao_spider(db_cj,url_page=u"http://bj.lianjia.com/chengjiao/pg1rs%E5%86%A0%E5%BA%AD%E5%9B%AD"):
    """
    爬取页面链接中的成交记录
    """
    try:
        req = urllib2.Request(url_page,headers=hds[random.randint(0,len(hds)-1)])
        source_code = urllib2.urlopen(req,timeout=10).read()
        plain_text=unicode(source_code)#,errors='ignore')   
        soup = BeautifulSoup(plain_text, "html.parser")
    except (urllib2.HTTPError, urllib2.URLError), e:
        print e
        exception_write('chengjiao_spider',url_page)
        exit(-1)
    except Exception,e:
        print e
        exception_write('chengjiao_spider',url_page)
        exit(-1)

    communityid=url_page.split('/')[4].split('c')[1]
#    print communityid
    cj_list=soup.findAll('div',{'class':'info'})
    for cj in cj_list:
        info_dict={}
        content=cj.find('div', {'class':'title'})
        if content:
            a=content.find('a')
            if not a:
                continue
            print "         %s" % a 
            text=a.text.split()
            url_seg = a.get('href').strip().split('/')
            if len(url_seg) != 5:
                print "Error! parsing xiaoquid fail in xiaoqu %s in region page %s" % (xq_url, url_page)
                continue

            info_dict.update({u'house_id':url_seg[4].split('.')[0]})
            info_dict.update({u'community_id':communityid})
            info_dict.update({u'community_name':text[0]})
            info_dict.update({u'room_num':text[1]})
            info_dict.update({u'area':text[2]})

        content=cj.find('div', {'class':'address'})
        if content:
            houseInfo=content.find('div', {'class':'houseInfo'})
            if not houseInfo:
                print "Error! No houseInfo"
                continue
            text=houseInfo.text.strip().split('|')
            info_dict.update({u'direction':text[0].strip()})
            info_dict.update({u'decorator':text[1].strip()})

            dealDate=content.find('div', {'class':'dealDate'})
            if not dealDate:
                print "Error! No dealDate"
                continue
            info_dict.update({u'dealtime':dealDate.text.strip()})

            totalPrice=content.find('div', {'class':'totalPrice'})
            if not totalPrice:
                print "Error! No totalPrice"
                continue
            info_dict.update({u'total_price':totalPrice.text.strip()})

        content=cj.find('div', {'class':'flood'})
        if content:
            positionInfo=content.find('div', {'class':'positionInfo'})
            if not positionInfo:
                print "Error! No positionInfo"
                continue
            info_dict.update({u'floor':positionInfo.text.strip()})

            source=content.find('div', {'class':'source'})
            if not source:
                print "Error! No source"
                continue
            info_dict.update({u'agent':source.text.strip()})

            unitPrice=content.find('div', {'class':'unitPrice'})
            if not unitPrice:
                print "Error! No unitPrice"
                continue
            info_dict.update({u'unit_price':unitPrice.text.strip()})
            
        content=cj.find('div', {'class':'dealHouseInfo'})
        if content:
            dealHouseTxt=content.find('span', {'class':'dealHouseTxt'})
            if dealHouseTxt:
                dealHouseTxt=dealHouseTxt.findAll('span')
#                print dealHouseTxt
                for attr in dealHouseTxt:
                    attr=attr.text.strip()
                    if attr.find(u'满')!=-1:
                        info_dict.update({u'house_type':attr.strip()})
                    elif attr.find(u'学')!=-1:
                        info_dict.update({u'school_type':attr.strip()})
                    elif attr.find(u'距')!=-1:
                        info_dict.update({u'subway_type':attr.strip()})
        print "         result size:%d" % len(info_dict.keys())
        command=gen_chengjiao_insert_command(info_dict)
        db_cj.execute(command,1)


def xiaoqu_chengjiao_spider(db_cj,xq_id=u"1111027375142"):
    """
    爬取小区成交记录
    """
    url=u"http://bj.lianjia.com/chengjiao/c"+xq_id+"/"
    print "crawl xiaoqu %s, %s" % (xq_id, url)
    try:
        req = urllib2.Request(url,headers=hds[random.randint(0,len(hds)-1)])
        source_code = urllib2.urlopen(req,timeout=10).read()
        plain_text=unicode(source_code)#,errors='ignore')   
        soup = BeautifulSoup(plain_text, "html.parser")
    except (urllib2.HTTPError, urllib2.URLError), e:
        print e
        exception_write('xiaoqu_chengjiao_spider',xq_name)
        return
    except Exception,e:
        print e
        exception_write('xiaoqu_chengjiao_spider',xq_name)
        return

    content=soup.find('div',{'class':'page-box house-lst-page-box'})
    total_pages=0
    if content:
        d="d="+content.get('page-data')
        exec(d)
        total_pages=d['totalPage']

    print "total pages:%d" % total_pages
    if total_pages == 0:
        url_page=u"http://bj.lianjia.com/chengjiao/pg1c%s/" % (urllib2.quote(xq_id))
        print "     %s" % url_page
        chengjiao_spider(db_cj,url_page)
    else:
        threads=[]
        for i in range(total_pages):
            url_page=u"http://bj.lianjia.com/chengjiao/pg%dc%s/" % (i+1,urllib2.quote(xq_id))
            print "     %s" % url_page
            chengjiao_spider(db_cj,url_page)
#            t=threading.Thread(target=chengjiao_spider,args=(db_cj,url_page))
#            threads.append(t)
#        for t in threads:
#            t.start()
#        for t in threads:
#            t.join()


def do_xiaoqu_chengjiao_spider(db_xq,db_cj):
    """
    批量爬取小区成交记录
    """
    count=0
    xq_list=db_xq.fetchall()
    for xq in xq_list:
        xiaoqu_chengjiao_spider(db_cj,xq[0])
        count+=1
        if count > 10:
            exit(-1)
    print 'done'

def exception_spider(db_cj):
    """
    重新爬取爬取异常的链接
    """

if __name__=="__main__":
    command="create table if not exists xiaoqu (community_id TEXT primary key UNIQUE, community_name TEXT, district TEXT, bizcircle TEXT, building_type TEXT, build_time TEXT, avg_price TEXT, stock TEXT, url TEXT)"
    db_xq=SQLiteWraper('lianjia-xq.db',command)

    command="create table if not exists chengjiao (house_id TEXT primary key UNIQUE, community_id TEXT, community_name TEXT, room_num TEXT, area TEXT, direction TEXT, decorator TEXT, dealtime TEXT, total_price TEXT, floor TEXT, agent TEXT, unit_price TEXT, houset_ype TEXT, school_type TEXT, subway_type TEXT)"
    db_cj=SQLiteWraper('lianjia-cj.db',command)

    #爬下所有的小区信息
#    for region in regions:
#        do_xiaoqu_spider(db_xq,region)

    #爬下所有小区里的成交信息
    do_xiaoqu_chengjiao_spider(db_xq,db_cj)

    #重新爬取爬取异常的链接
    exception_spider(db_cj)
