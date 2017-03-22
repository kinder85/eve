# -*- coding: utf-8 -*-

def process_args(args, param_string):
    """ Get the trigger and the response (or shortcut) from the args
    """
    the_args = u' '.join(args).split("__SEP__")
    print(the_args)
    the_trigger = the_args[0]
    the_trigger = the_trigger.replace(param_string, "*");
    the_response = the_args[1]
    # replace each parameter by <starX>
    tab_response = the_response.split(param_string)
    if len(tab_response) > 1:
        the_response = u""
        for idx_r in range(0, len(tab_response) - 1):
            the_response += u"{0} <star{1}>".format(tab_response[idx_r], idx_r + 1)
        the_response = u"{0} {1}".format(the_response, tab_response[-1])

    return the_trigger, the_response
            

