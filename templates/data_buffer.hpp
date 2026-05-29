#ifndef	DATA_BUFFER_HPP
# define DATA_BUFFER_HPP


#include <vector>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <memory>



class DataBuffer
{
    private:

        std::vector<std::byte>	_buffer;
		size_t					_read_position;


    public:

        DataBuffer();
        ~DataBuffer();
        DataBuffer(const DataBuffer &databuffer);
	    DataBuffer& operator=(const DataBuffer &databuffer);


		template<typename TType>

		DataBuffer& operator<<(const TType& data)
		{
			std::byte	*raw = reinterpret_cast<std::byte*>(std::addressof(data));

			_buffer.insert(_buffer.end(), raw , raw + sizeof(TType));

			return(*this);
		}


		template<typename TType>

		DataBuffer& operator>>(TType& data)
		{	
			if(_buffer.size() - _read_position < sizeof(TType))
			{
				throw std::out_of_range("DataBuffer: Not enough data to extract");
			}
			
			data = *reinterpret_cast<TType*>(*( _buffer.begin() + _read_position));

			_read_position += sizeof(TType);

			if(_read_position >= _buffer.size() / 2)
			{
				_buffer.erase(_buffer.begin(),  _buffer.begin() + _read_position - 1);
				_read_position = 0;
			}

			return(*this);
		}

		
	};



#endif