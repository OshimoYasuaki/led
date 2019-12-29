sudo chmod 666 /dev/myled0 

echo 1 > /dev/myled0
sleep 1s
echo 0 > /dev/myled0
sleep 5s
echo 1 > /dev/myled0
sleep 2s
echo 0 > /dev/myled0
