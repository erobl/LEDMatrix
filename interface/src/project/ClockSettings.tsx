import React, { Component } from 'react';
import { ValidatorForm } from 'react-material-ui-form-validator';
import { CompactPicker, HuePicker, ColorResult } from 'react-color';

import { Typography, Box, Checkbox, Slider } from '@material-ui/core';
import SaveIcon from '@material-ui/icons/Save';

import { ENDPOINT_ROOT } from '../api';
import { restController, RestControllerProps, RestFormLoader, RestFormProps, FormActions, FormButton, SectionContent, BlockFormControlLabel } from '../components';

import { ClockState } from './types';

export const CLOCK_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "clockSettings";

const flexContainerStyle = {
  alignContent: 'center',
  alignItems: 'center',
  display: 'flex',
  justifyContent: 'center',
};

type ClockStateRestControllerProps = RestControllerProps<ClockState>;

class ClockStateRestController extends Component<ClockStateRestControllerProps> {

  componentDidMount() {
    this.props.loadData();
  }

  render() {
    return (
      <SectionContent title='' titleGutter>
        <RestFormLoader
          {...this.props}
          render={props => (
            <ClockStateRestControllerForm {...props} />
          )}
        />
      </SectionContent>
    )
  }

}

export default restController(CLOCK_SETTINGS_ENDPOINT, ClockStateRestController);

type ClockStateRestControllerFormProps = RestFormProps<ClockState>;

function ClockStateRestControllerForm(props: ClockStateRestControllerFormProps) {
  const { data, setData, saveData, loadData, handleValueChange } = props;
  const handleColorChange = (color: ColorResult) => {
    setData({...data, 
            colorRed: color.rgb.r, 
            colorGreen: color.rgb.g,
            colorBlue: color.rgb.b
    });
  }
  console.log(data)
  return (
    <ValidatorForm onSubmit={saveData}>
      <Slider
        value={data.brightness}
        aria-labelledby="brightness-slider"
        valueLabelDisplay="on"
        min={0}
        max={255}
        onChange={(event, brightness) => { if (typeof brightness === 'number') { setData({...data, brightness}) } }}
      />
      <Box pt={5}>
          <div style={flexContainerStyle}>
            <HuePicker color={{r: data.colorRed, g: data.colorGreen, b: data.colorBlue}} onChangeComplete={handleColorChange} />
          </div>
      </Box>
      <Box pt={5}>
        <div style={flexContainerStyle}>
          <CompactPicker color={{r: data.colorRed, g: data.colorGreen, b: data.colorBlue}} onChangeComplete={handleColorChange} />
        </div>
      </Box>
      <FormActions>
        <FormButton startIcon={<SaveIcon />} variant="contained" color="primary" type="submit">
          Save
        </FormButton>
      </FormActions>
    </ValidatorForm>
  );
}
