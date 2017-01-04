select * from (select district, count(*) as community_num, sum(stock) as total_stock, avg(avg_price) as avgprice from xiaoqu where stock>0 group by district) t order by t.avgprice desc
