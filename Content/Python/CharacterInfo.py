import json


class CharacterInfo:
    def __init__(self, settings_file_path):
        with open(settings_file_path, 'r') as file:
            data = json.load(file)
            self.name = data['name']
            self.health = data['health']
            #Set the file paths
            self.filePath = f'/Game/Characters/{self.name}'
            self.selectIconPath = self.filePath + f'/ArtAssets/{data["selectIcon"]}'
