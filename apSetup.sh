sudo apt-get update
sudo apt-get install dnsmasq hostapd
sudo systemctl stop dnsmasq
sudo systemctl stop hostapd
cat <<EOF >>/etc/dhcpcd.conf
interface wlan0
    static ip_address=192.168.4.1/24
    nohook wpa_supplicant
EOF
sudo service dhcpcd restart
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
cat <<EOF >>/etc/dnsmasq.conf
interface=wlan0      # Use the require wireless interface - usually wlan0
  dhcp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h
EOF
cat <<EOF >/etc/hostapd/hostapd.conf
interface=wlan0
driver=nl80211
ssid=TempNet
hw_mode=g
channel=7
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=networkforthetemperaturesensors
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
EOF
sed -i 's~#DAEMON_CONF=""~DAEMON_CONF="/etc/hostapd/hostapd\.conf"~' /etc/default/hostapd
sudo systemctl start hostapd
sudo systemctl start dnsmasq
sed -i 's~#net\.ipv4\.ip_forward=1~net\.ipv4\.ip_forward=1~' /etc/sysctl.conf
sudo iptables -t nat -A  POSTROUTING -o eth0 -j MASQUERADE
sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"
sed -i '19s~.*~iptables-restore < /etc/iptables\.ipv4\.nat~' /etc/rc.local
