#include "File.h"

bool File::IsHandleValid(File::Handle fh) noexcept
{
	DWORD Flags;
	return GetHandleInformation(fh, &Flags);
}

File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
{
	//Verify the Handle isn't already in use
	if (!File::IsHandleValid(fh))
	{
		//check mode and create accordingly
		if (mode == File::Mode::READ)
		{
			fh = CreateFile(fileName, GENERIC_READ, 0, nullptr, 4, FILE_ATTRIBUTE_NORMAL, nullptr);
		}
		else if (mode == File::Mode::WRITE)
		{
			fh = CreateFile(fileName, GENERIC_WRITE, 0, nullptr, 4, FILE_ATTRIBUTE_NORMAL, nullptr);
		}
		else
		{
			fh = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, 4, FILE_ATTRIBUTE_NORMAL, nullptr);
		}

		if (fh != nullptr && fh != INVALID_HANDLE_VALUE)
		{
			//Verify that the handle was created successfully.
			return File::Error::SUCCESS;
		}
	}
	//Fail return
	return File::Error::OPEN_FAIL;
}

File::Error File::Close(const File::Handle fh) noexcept
{
	//Verify Handle is valid
	if (File::IsHandleValid(fh))
	{
		//Close if so
		if (CloseHandle(fh))
		{
			return File::Error::SUCCESS;
		}
	}
	//Otherwise fail
	return File::Error::CLOSE_FAIL;
}

File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
{
	//Verify Handle is valid
	if (File::IsHandleValid(fh))
	{
		if (WriteFile(fh, buffer, inSize, nullptr, nullptr))
		{
			//Write to file. If this failed, it won't trigger this return.
			return File::Error::SUCCESS;
		}
	}
	return File::Error::WRITE_FAIL;
}

File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
{
	if (File::IsHandleValid(fh))
	{
		//Verify Handle is valid.
		if (ReadFile(fh, buffer, inSize, nullptr, nullptr))
		{
			//Read from file. If this failed, it won't trigger this return.
			return File::Error::SUCCESS;
		}
	}
	return File::Error::READ_FAIL;
}

File::Error File::Seek(File::Handle fh, File::Location location, int offset) noexcept
{
	if (File::IsHandleValid(fh))
	{
		//Verify Handle is valid and check location.
		if (location == File::Location::BEGIN)
		{
			if (SetFilePointer(fh, offset, nullptr, 0) != INVALID_SET_FILE_POINTER)
			{
				return File::Error::SUCCESS;
			}
		}
		else if (location == File::Location::CURRENT)
		{
			if (SetFilePointer(fh, offset, nullptr, 1) != INVALID_SET_FILE_POINTER)
			{
				return File::Error::SUCCESS;
			}
		}
		else
		{
			if (SetFilePointer(fh, offset, nullptr, 2) != INVALID_SET_FILE_POINTER)
			{
				return File::Error::SUCCESS;
			}
		}
	}
	return File::Error::SEEK_FAIL;
}

File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
{
	if (File::IsHandleValid(fh))
	{
		//Pull the current location by sending a 0 move at current location. 
		offset = SetFilePointer(fh, 0, nullptr, 1);
		if (offset != INVALID_SET_FILE_POINTER)
		{
			//Verify that the read was successful
			return File::Error::SUCCESS;
		}
	}
	return File::Error::TELL_FAIL;
}

File::Error File::Flush(File::Handle fh) noexcept
{
	if (File::IsHandleValid(fh))
	{
		//Force write buffers to file. 
		if (FlushFileBuffers(fh))
		{
			return File::Error::SUCCESS;
		}
	}
	return File::Error::FLUSH_FAIL;
}
