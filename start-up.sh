kill -9 `ps aux | grep "upload" | grep -v grep | awk '{print $2}'`
spawn-fcgi -a 127.0.0.1 -p 8082 -f ./upload
#spawn-fcgi -a 127.0.0.1 -p 8012 -f ./test/main_test
#sudo /usr/local/nginx/sbin/nginx
#redis-server ./conf/redis.conf
#sudo fdfs_trackerd ./conf/tracker.conf
#sudo fdfs_storaged ./conf/storage.conf
