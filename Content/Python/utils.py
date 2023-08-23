import os

def find_settingsfiles(start_dir):
    """
    Walks through character directory and finds all files called 'settings.json'
    :param start_dir:
    :return:
    """
    settings_file_paths = []
    for root, dirs, files in os.walk(start_dir):
        if 'settings.json' in files:
            settings_file_paths.append(os.path.join(root, 'settings.json'))

    return settings_file_paths