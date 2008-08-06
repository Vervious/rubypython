#include "rubypython_bridge.h"

VALUE mRubyPythonBridge;
extern VALUE cRubyPyObject;
extern VALUE cRubyPyModule;
extern VALUE cRubyPyClass;


/*
call-seq: func(modname,funcname,*args)
Given a python module name _modname_ and a function name _funcname_ calls the given function
with the supplied arguments.

Use builtins as the module for a built in function.

*/
static VALUE func_with_module(VALUE self, VALUE args)
{
	int started_here=safe_start();
	VALUE module,func,return_val;
	if(RARRAY(args)->len<2) return Qfalse;
	module=rb_ary_shift(args);
	func=rb_ary_shift(args);
	return_val=rp_call_func_with_module_name(module,func,args);
	safe_stop(started_here);
	return return_val;
}

/*
* call-seq: import(modname)
* 
* Imports the python module _modname_ using the interpreter and returns a ruby wrapper
*/
static VALUE rp_import(VALUE self,VALUE mname)
{
	return rb_class_new_instance(1,&mname,cRubyPyModule);
}

/*
* call-seq: start()
*
* Starts the python interpreter
*/
VALUE rp_start(VALUE self)
{
	

	if(Py_IsInitialized())
	{
		return Qfalse;
	}
	Py_Initialize();
	return Qtrue;
}

/*
* call-seq: stop()
*
* Stop the python interpreter
*/
VALUE rp_stop(VALUE self)
{
	
	if(Py_IsInitialized())
	{
		Py_Finalize();
		return Qtrue;
	}
	return Qfalse;
	
}


/*
* Module containing an interface to the the python interpreter.
*
* Use RubyPython instead.
*/

void Init_rubypython_bridge()
{
	mRubyPythonBridge=rb_define_module("RubyPythonBridge");
	rb_define_module_function(mRubyPythonBridge,"func",func_with_module,-2);
	rb_define_module_function(mRubyPythonBridge,"start",rp_start,0);
	rb_define_module_function(mRubyPythonBridge,"stop",rp_stop,0);
	rb_define_module_function(mRubyPythonBridge,"import",rp_import,1);
	Init_RubyPyObject();
	Init_RubyPyModule();
	Init_RubyPyClass();
	Init_RubyPyFunction();
	Init_RubyPyError();
	Init_RubyPyInstance();
	
}