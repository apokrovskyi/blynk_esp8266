#ifndef buffer_h
#define buffer_h

class Buffer{
public:
    Buffer(size_t size)
    :_empty(true),
    _head(0),
    _tail(0),
    _size(size)
    {
        _buffer = new uint8_t[size];
    }
    
    size_t read(uint8_t* dst, size_t length);
    
    int available(){
        if(_empty) return 0; // also hepls to indicate when buffer is full
        
        if(_head == _tail) return _size; //buffer is full
        
        return (_tail - _head + _size) % _size;
    }
    
private:
    uint8_t* _buffer;
    size_t _size;
    
    size_t _head;
    size_t _tail;
    
    bool _empty;
    
    size_t write(const char* source, size_t length){ Serial.println("Buffer writing");
        if(!length) return 0;
        
        bool overwrite = length > _size - available();
        
        while(length>0){
            size_t chunk = _size - _tail;
            if(chunk > length) chunk = length;
            
            os_memcpy(_buffer + _tail, source, chunk);
            
            length -= chunk;
            source += chunk;
            _tail = (_tail + chunk) % _size;
        }
        
        if(overwrite){
            _head = _tail;
        }
        
        _empty = false;
    }
    
    friend void blynk_recv_cb(void* arg, char* data, unsigned short len);
};

size_t Buffer::read(uint8_t* dst, size_t length){ Serial.println("Buffer reading");
        if(_empty || !length) return 0;
        
        size_t read = 0;
        
        while(read<length){
            size_t chunk = _size - _head;
            if(chunk > available()) chunk = available();
            if(chunk > length) chunk = length;
            
            os_memcpy(dst, _buffer + _head, chunk);
            
            read += chunk;
            dst += chunk;
            _head = (_head + chunk) % _size;
            
            if(_head == _tail){
                _empty = true;
                break;
            }
        }
        
        return read;
    }

#endif
