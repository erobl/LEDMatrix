import React, { Component } from 'react';
import { Link, withRouter, RouteComponentProps } from 'react-router-dom';

import {List, ListItem, ListItemIcon, ListItemText} from '@material-ui/core';
import SettingsRemoteIcon from '@material-ui/icons/SettingsRemote';
import ScheduleIcon from '@material-ui/icons/Schedule';

import { PROJECT_PATH } from '../api';

class ProjectMenu extends Component<RouteComponentProps> {

  render() {
    const path = this.props.match.url;
    return (
      <List>
        <ListItem to={`/${PROJECT_PATH}/demo/`} selected={path.startsWith(`/${PROJECT_PATH}/demo/`)} button component={Link}>
          <ListItemIcon>
            <SettingsRemoteIcon />
          </ListItemIcon>
          <ListItemText primary="Demo Project" />
        </ListItem>
        <ListItem to={`/${PROJECT_PATH}/clock/`} selected={path.startsWith(`/${PROJECT_PATH}/clock/`)} button component={Link}>
          <ListItemIcon>
            <ScheduleIcon />
          </ListItemIcon>
          <ListItemText primary="Clock" />
        </ListItem>
      </List>
    )
  }

}

export default withRouter(ProjectMenu);
