/************************************************************************
ECS:Python - Light-Weight C++ Library For Embedding Python Into C++
Copyright (c) 2012-2019 Marcus Tomlinson

This file is part of EcsPython.

The BSD 2-Clause License:
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
************************************************************************/

#include <EcsMacros.h>
#include <EcsPython.h>
#include <Python.h>

#include <string>

//=================================================================================================

int ( *_Ecs_ParseTuple )( PyObject*, const char*, ... ) = NULL;

typedef char* charptr;
typedef void* voidptr;

template PyObject* _Ecs_ToPyObject( const charptr& );
template PyObject* _Ecs_ToPyObject( const std::string& );
template PyObject* _Ecs_ToPyObject( const char& );
template PyObject* _Ecs_ToPyObject( const unsigned char& );
template PyObject* _Ecs_ToPyObject( const short& );
template PyObject* _Ecs_ToPyObject( const unsigned short& );
template PyObject* _Ecs_ToPyObject( const int& );
template PyObject* _Ecs_ToPyObject( const unsigned int& );
template PyObject* _Ecs_ToPyObject( const long& );
template PyObject* _Ecs_ToPyObject( const unsigned long& );
template PyObject* _Ecs_ToPyObject( const long long& );
template PyObject* _Ecs_ToPyObject( const unsigned long long& );
template PyObject* _Ecs_ToPyObject( const bool& );
template PyObject* _Ecs_ToPyObject( const double& );
template PyObject* _Ecs_ToPyObject( const float& );
template PyObject* _Ecs_ToPyObject( const voidptr& );

//=================================================================================================

void _EcsAddNewMethod( const char* methodName, PyCFunction methodPointer, int methodFlags )
{
    if ( _Ecs_ParseTuple == NULL )
    {
        _Ecs_ParseTuple = PyArg_ParseTuple;
    }

    PyMethodDef newMethod = {methodName, methodPointer, methodFlags, NULL};
    EcsPythonMethods.push_back( newMethod );
}

//-------------------------------------------------------------------------------------------------

template <class Type>
PyObject* _Ecs_ToPyObject( const Type& Value )
{
    if ( typeid( Type ) == typeid( char* ) )
        return PyUnicode_FromFormat( "%s", *( (char**)( &Value ) ) );
    else if ( typeid( Type ) == typeid( std::string ) )
        return PyUnicode_FromFormat( "%s", ( *( (std::string*)( &Value ) ) ).c_str() );
    else if ( typeid( Type ) == typeid( char ) )
        return PyUnicode_FromFormat( "%c", *( (char*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( unsigned char ) )
        return PyLong_FromUnsignedLong( *( (unsigned char*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( short ) )
        return PyLong_FromLong( *( (short*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( unsigned short ) )
        return PyLong_FromUnsignedLong( *( (unsigned short*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( int ) )
        return PyLong_FromLong( *( (int*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( unsigned int ) )
        return PyLong_FromUnsignedLong( *( (unsigned int*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( long ) )
        return PyLong_FromLong( *( (long*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( unsigned long ) )
        return PyLong_FromUnsignedLong( *( (unsigned long*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( long long ) )
        return PyLong_FromLongLong( *( (long long*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( unsigned long long ) )
        return PyLong_FromUnsignedLongLong( *( (unsigned long long*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( bool ) )
        return PyBool_FromLong( *( (unsigned char*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( double ) )
        return PyFloat_FromDouble( *( (double*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( float ) )
        return PyFloat_FromDouble( *( (float*)( &Value ) ) );
    else if ( typeid( Type ) == typeid( void* ) )
        return PyLong_FromUnsignedLongLong( *( (unsigned long long*)( &Value ) ) );
    else
        return NULL;
}

//-------------------------------------------------------------------------------------------------

PyObject* _Ecs_GetPythonNull()
{
    Py_INCREF( Py_None );
    return Py_None;
}

//=================================================================================================
