import unreal
import os
import CharacterInfo
from utils import find_settingsfiles

character_directory = "/Characters/"

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

def load_all_characters_info():
    for settings_file in find_settingsfiles(character_directory):
        character_info = CharacterInfo(settings_file)
        print(character_info.settings_file)




# This is the directory where your images are stored
image_directory = "/Game/PathToYourImages/"

# This is the directory where you want to save the created assets
destination_directory = "/Game/PathToYourUIElements/"

# List all the files in the image directory
all_files = unreal.EditorAssetLibrary.list_assets(image_directory)

# Filter only the PNG files (or whatever your format is)
png_files = [f for f in all_files if f.endswith(".png")]

for png_file in png_files:
    # Load the texture
    texture = unreal.EditorAssetLibrary.load_asset(png_file)

    # Assuming you have a UBlueprint class for W_CharacterPortrait
    # Create an instance of it and set its texture property
    portrait_blueprint_path = "/Game/PathToYourBlueprints/W_CharacterPortrait.W_CharacterPortrait"
    new_portrait = unreal.EditorAssetLibrary.load_asset(portrait_blueprint_path)
    new_portrait.set_editor_property("portrait_texture", texture)

    # Save the new asset
    asset_name = "Portrait_" + unreal.Paths.get_base_filename(png_file)
    unreal.EditorAssetLibrary.save_asset(destination_directory + asset_name)
