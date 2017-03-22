# -*- coding: utf-8 -*-
def color_command(log, devices, args, cfg_i18n):
    from domogik.butler.brain import do_command
    from domogik.butler.brain import remove_accents

    log.debug("color_command > get i18n informations")
    basic_colors = cfg_i18n['BASIC_COLORS']
    colors = cfg_i18n['COLORS']
    DONE = cfg_i18n['DONE']
    UNKNOWN_DEVICE = cfg_i18n['UNKNOWN_DEVICE']
    UNKNOWN_COLOR = cfg_i18n['UNKNOWN_COLOR']
    TXT_BASIC_COLORS_1 = cfg_i18n['TXT_BASIC_COLORS_1']
    TXT_BASIC_COLORS_2 = cfg_i18n['TXT_BASIC_COLORS_2']
    TXT_COLOR_LIST = cfg_i18n['TXT_COLOR_LIST']

    # put all keys lower case
    log.debug("color_command > preprocess color list")
    raw_colors = colors
    colors.update(basic_colors)
    colors = dict((remove_accents(k.lower()), v) for k, v in colors.iteritems())

    log.debug("color_command > process args")
    tab_args = ' '.join(args).split(",")
    print(tab_args)
    locale = tab_args[0].strip()
    dt_type_list = tab_args[1].strip()
    device = tab_args[2].strip()
    value = tab_args[3].strip()
    # optionnal parameter to get informations about a color
    if len(tab_args) > 4:
        arg4 = tab_args[4].strip()

    log.debug("color_command > do the action")
    if value in colors:
        value = colors[value]

    elif value == "listcolors":
        resp = u"{0}".format(TXT_BASIC_COLORS_1)
        for a_color in basic_colors:
            resp += u", {0}".format(a_color)
        resp += u". {0}".format(TXT_BASIC_COLORS_2)
        return resp

    elif value == "detailcolor":
        resp = u"{0} {1}".format(TXT_COLOR_LIST, arg4)
        search_color = remove_accents(arg4.lower())
        for a_color in raw_colors:
            the_color = remove_accents(a_color.lower())
            if search_color in the_color:
                resp += u", {0}".format(a_color)
        return resp

    else:
        return u"{0}".format(UNKNOWN_COLOR)
    res = do_command(log, devices, locale, dt_type_list=dt_type_list, device=device, value=value)
    if res == None:
        return u"{0} : {1}".format(UNKNOWN_DEVICE, device)
    else:
        return u"{0}".format(DONE)
