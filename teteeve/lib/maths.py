# -*- coding: utf-8 -*-
def calc(args, operands, bad_formula_msg):
    """ Calculte a formula
        @param args : raw formula
        @param operands : a dict like this (french) :
              OPERANDS = {u"plus" : "+",
                          u"moins" : "-",
                          u"fois" : "*",
                          u"divisepar" : "/"}
              warning: no spaces in the keys!!!
    """
    
    # processing
    formula = ""
    for a_arg in args:
        if a_arg in operands:
            formula += " {0} ".format(operands[a_arg])
        else:
            formula += a_arg
    
    try:
        result = eval(formula)
        voice_formula = formula.replace("*", "x")
    except:
        return u"{0}".format(bad_formula_msg)
    return "{0} = {1}".format(voice_formula, result)
