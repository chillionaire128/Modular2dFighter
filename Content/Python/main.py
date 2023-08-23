import unreal
import os
from CharacterInfo import CharacterInfo
from CharacterLoadingUtils import get_all_characters_info

character_directory = "E:/Unreal/Modular2dFighter/Modular2dFighter/Content/Characters/"

character_info = get_all_characters_info(character_directory)
for character in character_info:
    print(f"Loaded info for: {character.name}")

# List all the files in the image directory
#all_files = unreal.EditorAssetLibrary.list_assets(image_directory)

# Filter only the PNG files (or whatever your format is)
#png_files = [f for f in all_files if f.endswith(".png")]

#for png_file in png_files:
    # Load the texture
#    texture = unreal.EditorAssetLibrary.load_asset(png_file)

    # Assuming you have a UBlueprint class for W_CharacterPortrait
    # Create an instance of it and set its texture property
#    portrait_blueprint_path = "/Game/PathToYourBlueprints/W_CharacterPortrait.W_CharacterPortrait"
#    new_portrait = unreal.EditorAssetLibrary.load_asset(portrait_blueprint_path)
#    new_portrait.set_editor_property("portrait_texture", texture)

    # Save the new asset
#    asset_name = "Portrait_" + unreal.Paths.get_base_filename(png_file)
#    unreal.EditorAssetLibrary.save_asset(destination_directory + asset_name)
