# meteo-zone2
Novosibirsk meteo project
<h2>Meteo Pi client</h2><br>
<b>Depedencies (Debian):</b>
````
apt install git gcc make
````
<b>Installation:</b>
````
git clone https://github.com/LittleBuster/meteo-zone2.git
cd meteo-zone2
cd pi
make
make install
cd /etc/systemd/system/
cp sshd.service meteo.service
vim meteo.service

#change ExecStart to "ExecStart=/usr/share/meteo/meteo"
#change Alias to "Alias=meteo.service"
#delete "EnvironmentFile=-/etc/default/ssh"

vim /etc/meteosrv.conf
````
<h2>Meteo server</h2><br>
<b>Depedencies (Debian):</b>
````
apt install git gcc make
````
<b>Installation:</b>
````
git clone https://github.com/LittleBuster/meteo-zone2.git
cd meteo-zone2
cd server
make
make install
cd /etc/systemd/system/
cp sshd.service meteosrv.service
vim meteosrv.service

#change ExecStart to "ExecStart=/usr/share/meteosrv/meteosrv"
#change Alias to "Alias=meteosrv.service"
#delete "EnvironmentFile=-/etc/default/ssh"

vim /etc/meteosrv.conf
````
<br>
Developed by: <b>Sergey Denisov</b>
<br>
Email: <b>DenisovS21@gmail.com</b>
