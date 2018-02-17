/*
 Client.h - Base class that provides Client
 Copyright (c) 2011 Adrian McEwen.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef client_h
#define client_h
#include "IPAddress.h"
#include "user_interface.h"

extern"C"{
#include "espconn.h"
}

void host_ip_callback(const char *name, ip_addr_t *ipAddr, void *arg);

class Client{

    public:
        Client()
        :_ipAddr()
        {
            _conn.type = ESPCONN_TCP;
            _conn.state = ESPCONN_NONE;
            _conn.proto.tcp = &_tcp;
        }
    
        int connect(IPAddress ip, uint16_t port){   Serial.println("connect ip");
            BLYNK_LOG_IP("IP: ", ip);
            
            _tcp.remote_port = port;
            memcpy(_tcp.remote_ip, ip.raw_address(), 4);
            espconn_connect(&_conn);
        }
        
        int connect(const char *host, uint16_t port){   Serial.println("connect host");
            if(_ipAddr){
                connect(_ipAddr, port);
            }
            else{
                espconn_gethostbyname((struct espconn*)(void*)this, host, (ip_addr_t*)_ipAddr.raw_address(), (dns_found_callback)host_ip_callback);
            }
        }
        
        void setTimeout(unsigned long timeout){ Serial.println("set timeout");}
        
        size_t write(uint8_t){  Serial.println("write");}
        
        size_t write(const uint8_t *buf, size_t size){Serial.println("writes");}
        
        int available(){Serial.println("available");}
        
        int read(){Serial.println("read");}
        
        int read(uint8_t *buf, size_t size){Serial.println("reads");}
        
        int peek(){Serial.println("peek");}
        
        void flush(){Serial.println("flush");}
        
        void stop(){Serial.println("stop");
            
            if(connected()){
                _ipAddr = (uint32_t)0;
            
                espconn_disconnect(&_conn);
            }
        }
        
        uint8_t connected(){    Serial.println("connected");
            return _conn.state != ESPCONN_CLOSE && _conn.state != ESPCONN_NONE; 
        }
        
        operator bool(){Serial.println("booled");}
        
        size_t readBytes( char *buffer, size_t length){Serial.println("readBytes");}
        
        size_t readBytes( uint8_t *buffer, size_t length) { return readBytes((char *)buffer, length); }
    protected:
        uint8_t* rawIPAddress(IPAddress& addr) {
            return addr.raw_address();
        }
        ;
    private:
        friend void host_ip_callback(const char *name, ip_addr_t *ipAddr, void *arg);
    
        IPAddress _ipAddr;
        struct espconn _conn;
        esp_tcp _tcp;
};

void host_ip_callback(const char *name, ip_addr_t *ipAddr, void *arg)
{
     ((Client*)arg)->_ipAddr = ipAddr->addr;
}

#endif
