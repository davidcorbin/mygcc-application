# MyGCC App Requirements

### Beautiful
- Clean, simple design
- Native feeling on all platforms
- Lightweight feeling

### Functional
- Most useful information first

### Features
- Cross platform notifications
- High DPI screen support
- Auto updating GUI application and API
- Check and notify when data has changed on myGCC
- Anonymous error logging and reporting
   - Use a Slack channel to receive feedback and logged errors
- Glance integration
- Save encrypted string, initvect, enc key to disk
- Customize what APIs are on the front page

### Timeline 
- Paper design
- Photoshop design
- GUI application with fake data
- Read only application with simple
- Read only application with all APIs
- Write capability 

### Ideas
- Run the server when the user puts the application in the foreground
- Run the server when the windows is open

### Updating
#### Expected Updates
1. A new release is created.
1. On startup, the application shows a popup that there is an update available, the user can decide to postpone the update.
   1. User updates:
      1. Application is updated to newest version.
   1. User postpones the update:
      1. There will be a persistent bright icon that will also trigger the update process.
      1. User cannot give feedback until they update.
      1. A week after postponing the application will not work without an update.

#### Required Updates
1. A new release is created.
1. On startup the application shows a popup that there is an update available, the user can postpone the update.
   1. User updates:
      1. Application is updated to newest version.
   1. User postpones the update:
      1. There will be a persistent bright icon that will also trigger the update process.
      1. User cannot give feedback until they update.
      1. The application will not work without an update.

#### Emergency Updates
1. A new release is created.
1. **The update breaks the application** (assume worst-case the application will not open), there is no way to update through the application.
1. An emergency release is created.
1. An email containing a link to update will be sent out to users who have used the application recently (i.e. last month).

## Future Plans
### Features
- Interactive tiles on home screen. (That can display more information about the thing)
- Download file to location by clicking on tile, remember where file is saved, so if tile is clicked again open the file rather than download again.
