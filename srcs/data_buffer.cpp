#include "data_buffer.hpp"

DataBuffer::DataBuffer(): _read_position(0){}

DataBuffer::DataBuffer(const DataBuffer &databuffer): _buffer(databuffer._buffer), _read_position(databuffer._read_position){}

DataBuffer::~DataBuffer(){}

DataBuffer&	DataBuffer::operator=(const DataBuffer &databuffer)
{
	_buffer = databuffer._buffer;
	_read_position = databuffer._read_position;

	return (*this);
}