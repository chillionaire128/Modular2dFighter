import os
from CharacterInfo import CharacterInfo

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

def get_all_characters_info(character_directory):
    """
    Checks for settings files inside character directory and
    initializes a CharacterInfo object based on info in the JSON file
    :param character_directory: Path to the base directory containing the character folders
    :return: List of CharacterInfo
    """
    characters_to_load = []
    for settings_file in find_settingsfiles(character_directory):
        characters_to_load.append(CharacterInfo(settings_file))
    return characters_to_load
